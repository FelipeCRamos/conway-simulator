#include "generation.hpp"
#include "canvas.hpp"

Gen::Gen( const int SIZE ){
	// Object Gen Constructor that creates an bidimensional canvas size * size.
	this->screen = new Canvas(SIZE, SIZE);
}

Gen::~Gen( void ){
	// Object Gen destructor
	delete this->screen;
}

bool Gen::next( void ){
	int counter = 0; 	// A simple counter variable, to simplify things

	// If the had_changed stays false in the entire function, it means that the
	// generation is stable.
	bool had_changed = false;

	for( int i = 0; i < this->screen->height; i++ ){
		for( int j = 0; j < this->screen->width; j++ ){
			this->screen->pixel[i][j].nearby = check_nearby( i, j );	
			counter = this->screen->pixel[i][j].nearby;
			bool is_alive = screen->pixel[i][j].is_alive();

			if( counter <= 1 ){
				// cell dies
				had_changed = this->screen->pixel[i][j].set_next(false, had_changed);
			}

			else if( counter >= 4 and is_alive == true){
				// cell dies
				had_changed = this->screen->pixel[i][j].set_next(false, had_changed);
			}

			else if( (counter == 2 or counter == 3) and is_alive == true){
				// cell remains alive
				had_changed = this->screen->pixel[i][j].set_next(true, had_changed);
			}

			else if( is_alive == false and counter == 3 ){
				// cell borns
				had_changed = this->screen->pixel[i][j].set_next(true, had_changed);
			}
	
			else {
				// cell remains dead
				had_changed = this->screen->pixel[i][j].set_next(false, had_changed);
			}
		}
	}
	if( had_changed == false ){
		std::cout << "Stable / Extint!" << std::endl;
		return true;	// it's stable } else {
		std::cout << "Not Stable!" << std::endl;
		return false;	// it's not stable
	}
	return false;
}

void Gen::update( void ){
	for( int i = 0; i < this->screen->height; i++ ){
		for( int j = 0; j < this->screen->width; j++ ){
			this->screen->pixel[i][j].update();
		}
	}
}

void Gen::random_it( void ){
	std::mt19937 random (std::chrono::system_clock::now().time_since_epoch().count());
	for(int i = 0; i < screen->height; i++){
		for(int j = 0; j < screen->width; j++){
			screen->pixel[i][j].rand_alive(random() % 2, random() % 2);
		}
	}
}

void Gen::print( char sep, char alive_c, char dead_c ){
	screen->print(sep, alive_c, dead_c);
}

Borders *Gen::correct_borders(  int height, int width, Borders *fix_border ){
	
	if( height == 0 )
		fix_border->ymin = 0;
	if( width == 0 )
		fix_border->xmin = 0;
	if( height == screen->height-1 )
		fix_border->ymax = 0;
	if( width == screen->width-1 )
		fix_border->xmax = 0;

	return fix_border;
}

int Gen::check_nearby( int height, int width ){
	Borders *border = new Borders;
	int count = 0;

	if(
		!( height <= 0 and height >= screen->height - 1 ) or 
		( width <= 0 and width >= screen->width - 1 )
	){
		border = correct_borders( height, width, border );
	}

	for( int i = border->ymin; i <= border->ymax; i++ ){
		for( int j = border->xmin; j <= border->xmax; j++ ){
			if( i == 0 and j == 0 ){
			} else{
				if( screen->pixel[height+i][width+j].is_alive() == true )
					count++;
			}
		}
	}	

	delete border;
	return count;
}
