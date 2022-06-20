#include "flowField.h"

flowField::flowField(sf::RenderWindow *_window,const int &_nx,const int &_ny, const unsigned& seed) : window(_window),nx(_nx),ny(_ny),noise(seed),grid(_nx,std::vector<std::pair<Vec2f,float>>(_ny))
{	
	resize();
	this->scale = 1.1;
	for (int x = 0; x < grid.size(); x++) {
		for (int y = 0; y < grid[x].size(); y++) {
			Vec3f deriv(0,0,0);
			float var = noise.eval(Vec3f(x * scale, y * scale, 1.0), deriv);
			grid[x][y] = std::pair<Vec2f,float>{Vec2f(std::cos(var * M_PI), std::sin(var * M_PI)),var * 360};
		}
	}
	resize();
	//sf::RectangleShape var(sf::Vector2f(2, 0.2));
	//var.setFillColor(sf::Color::White);
	//var.setOrigin(sf::Vector2f(var.getPosition().y / 2, 0.0));
	//auto windowSize = window->getSize();
	//for (int x = 0; x < visualVectors.size(); x++) {
	//	for (int y = 0; x < visualVectors[x].size(); y++) {
	//		visualVectors[x][y] = var;
	//		visualVectors[x][y].setPosition(sf::Vector2f(grid[x][y].first.x * windowSize.x, grid[x][y].first.y * windowSize.y));
	//		visualVectors[x][y].setRotation(grid[x][y].second);
	//	}
	//}
	
}

flowField::~flowField()
{
}

void flowField::setWindow(sf::RenderWindow *_window)
{
	window = _window;
}

void flowField::setScale(const float& _scale)
{
	this->scale = _scale;
}

void flowField::setXnumber(const int& _nx)
{
	this->nx = _nx;
}

void flowField::setYnumber(const int& _ny)
{
	this->ny = _ny;
}

void flowField::setNewSeed(const unsigned& seed)
{	
	noise = PerlinNoise(seed);
}

void flowField::setAnimation(const bool& _arg)
{
	yAnimation = _arg;
}

void flowField::setAnimationSpeed(const float& _speed)
{
	this->ySpeed = _speed;
}

void flowField::setDrawable(const bool& _arg)
{
	this->visualize = _arg;
}

void flowField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int x = 0; x < visualVectors.size(); x++) {
		for (int y = 0; y < visualVectors[x].size(); y++) {
			target.draw(visualVectors[x][y]);
		}
	}

}

void flowField::update(sf::Time elapsed)
{
	auto windowSize = window->getSize();
	int x = 0;
	int y = 0;
	if (yAnimation) {
		Time += elapsed;
		for (int x = 0; x < grid.size(); x++) {
			for (int y = 0; y < grid[x].size(); y++) {
				Vec3f deriv(0, 0, 0);
				float var = (noise.eval(Vec3f(x * scale, y * scale, Time.asSeconds() * ySpeed), deriv));
				if (x == 1 && y == 1) {
					//std::cerr << var << std::endl;
				}
				grid[x][y] = std::pair<Vec2f, float>{ Vec2f(std::cos(var * M_PI), std::sin(var * M_PI)),var * 360 };
			}
		}
	}
	for (auto row = visualVectors.begin(); row != visualVectors.end(); row++) {
		for (auto col = row->begin(); col != row->end(); col++) {
			col->setRotation(grid[x][y].second);
			y++;
		}
		y = 0;
		x++;
	}
}

Vec2f flowField::getVelocityVector(const Vec2f& _pos)
{	
	auto windowSize = window->getSize();
	std::cerr << _pos.x << ", " << _pos.y << std::endl;
	int x = (int) (_pos.x +  windowSize.x / nx /2) * nx / windowSize.x;
	int y = (int) (_pos.y +  windowSize.y / ny /2) * ny / windowSize.y;
	if (x > nx - 1) {
		x = 0;
	}
	if (y > ny - 1) {
		y = 0;
	}
	return grid[x][y].first;
}

void flowField::recalc()
{	
	for (int x = 0; x < grid.size(); x++) {
		for (int y = 0; y < grid[x].size(); y++) {
			Vec3f deriv(0, 0, 0);
			float var = noise.eval(Vec3f(x * scale, y * scale, 1.0), deriv);
			grid[x][y] = std::pair<Vec2f, float>{ Vec2f(std::cos(var * M_PI), std::sin(var * M_PI)),var * 360 };
		}
	}
}

void flowField::resize()
{
	grid.resize(this->nx, std::vector<std::pair<Vec2f, float>>(ny));
	visualVectors.resize(this->nx, std::vector<sf::RectangleShape> (ny, sf::RectangleShape()));
	recalc();
	auto windowSize = window->getSize();
	int x = 0;
	int y = 0;
	for (auto row = visualVectors.begin(); row != visualVectors.end(); row++) {
		for (auto col = row->begin(); col != row->end(); col++) {
			
			col->setSize(sf::Vector2f(16, 4));
			col->setOrigin(sf::Vector2f(0, col->getSize().y / 2));
			col->setFillColor(sf::Color::White);
			col->setPosition(sf::Vector2f((float)x * windowSize.x/nx,(float) y * windowSize.y/ny));
			col->setRotation(grid[x][y].second);
			y++;
		}
		y = 0;
		x++;
	}
}
