#include "include/SFML/Window.hpp"
#include "include/SFML/Graphics.hpp"
#include<cstddef>
#include<random>


namespace
{
    namespace params
    {
        constexpr static inline const std::size_t SCREEN_WIDE = 1920;
        constexpr static inline const std::size_t SCREEN_HEIGHT = 1080;
        constexpr static inline const std::size_t FRAMELIMIT = 2;
        constexpr static inline const std::size_t max_count_of_squares = 50;
        constexpr static inline const std::size_t min_count_of_squares = 15;
        constexpr static inline const std::size_t min_size_of_square = 10;
        constexpr static inline const std::size_t max_size_of_square_in_proportion_of_screen = 3;

    }
}

static std::size_t generate_random()
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution uid(1,std::numeric_limits<int>::max());
    return uid(mt);
}

static void do_draw(sf::RenderWindow& w)
{
    std::size_t count_of_squares = generate_random() % 
        (params::max_count_of_squares-params::min_count_of_squares) + params::min_count_of_squares;

    sf::RectangleShape square_for_draw;
    for(std::size_t i = 0; i < count_of_squares; ++i)
    {
        square_for_draw.setFillColor(sf::Color(
            generate_random()%256,//Red
            generate_random()%256,//Green
            generate_random()%256 //Blue
        ));
        square_for_draw.setPosition(
            generate_random()%params::SCREEN_WIDE,
            generate_random()%params::SCREEN_HEIGHT
        );;
        float square_size = generate_random()%(std::min(params::SCREEN_HEIGHT,params::SCREEN_WIDE)/params::max_size_of_square_in_proportion_of_screen-params::min_size_of_square)+params::min_size_of_square;
        square_for_draw.setSize(sf::Vector2f(square_size,square_size));
        w.draw(square_for_draw);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(params::SCREEN_WIDE,
                                    params::SCREEN_HEIGHT),
                      "My window");
    
    window.setFramerateLimit(params::FRAMELIMIT);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
		do_draw(window);////////////
		window.display();


    }

    return 0;
}