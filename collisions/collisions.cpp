

/***
    Things that I implemented so far:
        basic particle class, basic collision detection, collision resolusion


    Problems:

        1. In collision resolusion, I made it so that when the particles are moving away from each other
        their velocities are not updated even though they are colliding. I did this because previously
        when this was not implemented, there were some issues that cause jittery movement when the velocities
        of the colliding particles are changed but they are still colliding in the next frame.

        2. When the particles are moving in high speed, sometimes they are tunneling through other particles that
        they would likely collide with. Mostly happens to small particles as only they have enough momentum to
        move such distances in a singel frame.


    Things that I NEED to implement:

        1. Tunneling resolution: Both of the particle tunneling and the tunneling through the walls

        2. Broad-Phase particle Collision: Need to implement this. Its fine for now as there are very less
        particles but as the no. of particles increase the current method becomes impracticle.

        3. Custom Boundries: Right now, the boundry box is the display window, I need implement it such that the
        boundry box can be customized with the same window size. Also, so that the simulation can be run of boundries
        of different shapes. Like a circle, square, triangle, etc.

        4. Maybe add something so that when the particles are spawned in, they don't intersect? I don't think this
        is that tough, maybe try this first?
            *** INITIAL IMPLEMENTAION IS DONE, but there are a few bugs, the initial spawn points are correct but
            if the new spawn is small and the distance between the points is less then there is a chance of the small
            particle to spawn inside of the bigger particle
***/


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace sf;


class particle
{
public:
    CircleShape circle;
    Vector2f acceleration;
    Vector2f velocity;
    float mass;


    particle()
    {
        circle = CircleShape();
        acceleration = Vector2f(0, 0);
        velocity = Vector2f(0, 0);
        mass = 0.f;
    }

    particle(float radius, Vector2f position, Vector2f acceleration, Vector2f velocity)
    {
        circle = CircleShape(radius);
        circleIntialization();
        circle.setPosition(position);
        this->acceleration = acceleration;
        this->velocity = velocity;
        this->mass = radius / 10.0f;
    }

    void update(int dt, Vector2f window_size)
    {
        checkBoundryCollisionAndResolution(window_size);

        velocity += acceleration * float(1.0 / dt);
        circle.move(velocity * float(1.0 / dt));
    }

    // Haven't implemented acceleration of this so it will probably break when that happens


private:

    void circleIntialization()
    {
        float radius = circle.getRadius();
        circle.setOrigin(radius, radius);
        circle.setFillColor(Color(255, 255, 255));
    }

    void checkBoundryCollisionAndResolution(Vector2f window_size)
    {
        Vector2f pos = circle.getPosition();
        float radius = circle.getRadius();


        if (pos.x + radius >= window_size.x)
        {
            if (velocity.x > 0) velocity.x = -velocity.x;
        }
        if (pos.x - radius <= 0)
        {
            if (velocity.x < 0) velocity.x = -velocity.x;
        }
        if (pos.y + radius >= window_size.y)
        {
            if (velocity.y > 0) velocity.y = -velocity.y;
        }
        if (pos.y - radius <= 0)
        {
            if (velocity.y < 0) velocity.y = -velocity.y;
        }
    }

};

float dotProduct(Vector2f const& v, Vector2f const& u)
{
    // Dot product of 2 vectors
    return float(u.x * v.x + u.y * v.y);

}

float distance(Vector2f vec1, Vector2f vec2)
{
    // Distance calculation between two circles
    return sqrt((vec1.x - vec2.x) * (vec1.x - vec2.x) + (vec1.y - vec2.y) * (vec1.y - vec2.y));
}

void particleCollisionResolution(particle& a, particle& b)
{
    Vector2f un = (a.circle.getPosition() - b.circle.getPosition());
    un = un / (sqrt(un.x * un.x + un.y * un.y)); // unit normal vector
    Vector2f ut = Vector2f(-un.y, un.x);    // unit tangent vector

    // value of the x and y vales of the initial vectors projected on unit normal and tangent
    float v1n = dotProduct(a.velocity, un), v1t = dotProduct(a.velocity, ut), v2n = dotProduct(b.velocity, un), v2t = dotProduct(b.velocity, ut);


    // value of the x and y vales of the final vectors projected on unit normal and tangent
    float v_1n = (v1n * (a.mass - b.mass) + 2 * b.mass * v2n) / (a.mass + b.mass), v_1t = v1t;
    float v_2n = (v2n * (b.mass - a.mass) + 2 * a.mass * v1n) / (a.mass + b.mass), v_2t = v2t;

    // final vectors
    Vector2f v1n__ = un * v_1n, v1t__ = ut * v_1t, v2n__ = un * v_2n, v2t__ = ut * v_2t;

    a.velocity = v1n__ + v1t__;
    b.velocity = v2n__ + v2t__;

}


int checkParticleCollision(vector<particle>& s, int i)
{
    Vector2f vec1 = s[i].circle.getPosition();
    float r1 = s[i].circle.getRadius();

    for (int j = i + 1; j < s.size(); j++)
    {


        Vector2f vec2 = s[j].circle.getPosition();
        float dis = distance(vec1, vec2);
        float r2 = s[j].circle.getRadius();

        if (dis < r1 + r2)
            return j;
        // particleCollisionResolution(s[i], s[j]);

    }
    return -1;
}



int main()
{
    // Create the main window
    Vector2f window_size = Vector2f(800, 600);
    RenderWindow window(VideoMode(window_size.x, window_size.y), "SFML window");
    int framerate = 60;
    window.setFramerateLimit(framerate);


    bool is_running = true;

    int no_of_particles = 50;

    int max_particle_size = 30;

    int min_particle_size = 10;

    Vector2f particle_position = Vector2f(0, 0);

    Vector2f particle_velocity = Vector2f(250, 250);

    Vector2f particle_acceleration = Vector2f(0, 0);

    int grid_buffer = 100;
    int grid_no = (int)sqrt(no_of_particles) + 1;
    int row = 0, col = 0;


    vector<particle> s;
    for (int i = 0; i < no_of_particles; i++)
    {
        if (row >= grid_no)
        {
            row = 0;
            col++;
        }


        float r = 0;
        while (r < min_particle_size)
            r = rand() % max_particle_size;

        particle_position = Vector2f((grid_buffer / 2) + row * ((window_size.x - grid_buffer) / grid_no), (grid_buffer / 2) + col * ((window_size.y - grid_buffer) / grid_no));
        s.push_back(particle(r, particle_position, particle_acceleration, particle_velocity));

        row++;
    }



    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }


        for (int i = 0; i < no_of_particles; i++)
        {
            int m = 0;
            int t = checkParticleCollision(s, i);

            // Check which particle (t) 'i' is colliding with
            if (t != -1)
            {
                // If the distance between the particles is reducing then change velocity
                if (distance(s[i].circle.getPosition(), s[t].circle.getPosition()) > distance(s[i].circle.getPosition() + (s[i].velocity * float(1.0 / framerate)), s[t].circle.getPosition() + (s[t].velocity * float(1.0 / framerate))))
                    particleCollisionResolution(s[i], s[t]);
            }

            s[i].update(framerate, window_size);
            s[t].update(framerate, window_size);
        }


        // Clear screen
        window.clear();


        for (int i = 0; i < no_of_particles; i++)
            window.draw(s[i].circle);


        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
