#include "flowField.h"

flowField::flowField(sf::RenderWindow *_window,const int &_nx,const int &_ny, const unsigned& seed) : window(_window),nx(_nx),ny(_ny),noise(seed),grid(_nx,std::vector<std::pair<Vec2f,float>>(_ny))
{	
	resize();
	this->scale = 1.1;
	for (int x = 0; x < grid.size() -1; x++) {
		for (int y = 0; y < grid[x].size(); y++) {
			Vec3f deriv(0,0,0);
			float var = noise.eval(Vec3f(x * scale, y * scale, 1.0), deriv)+1;
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
	_window = window;
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

void flowField::update(sf::Time)
{
}

Vec2f flowField::getVelocityVector(const Vec3f& _pos)
{
	return Vec2f();
}

void flowField::recalc()
{	
		
	visualVectors.resize(this->nx, std::vector<sf::RectangleShape> (ny));
	for (int x = 0; x < grid.size(); x++) {
		for (int y = 0; y < grid[x].size(); y++) {
			Vec3f deriv(0, 0, 0);
			float var = noise.eval(Vec3f(x * scale, y * scale, 1.0), deriv) + 1;
			grid[y][x] = std::pair<Vec2f, float>{ Vec2<float>(std::cos(var * M_PI), std::sin(var * M_PI)),var * 360};
		}
	}
	if (visualize) {
		for (int x = 0; x < visualVectors.size(); x++) {
			for (int y = 0; x < ny; y++) {
				visualVectors[x][y].setRotation(grid[x][y].second);
			}
		}
	}
}

void flowField::resize()
{
	grid.resize(this->nx, std::vector<std::pair<Vec2f, float>>(ny));
	//std::cerr << "Grid resized to:" << grid.size() << ", " << grid[grid.size()].size() << std::endl;
	//for (int x = 0; x < this->nx; x++) {
	//	std::vector<std::pair<Vec2f, float>> variable;
	//	for (int y = 0; y < this->ny; y++) {
	//		variable.push_back(std::pair)
	//	}
	//}


	visualVectors.resize(this->nx, std::vector<sf::RectangleShape> (ny, sf::RectangleShape()));

	//std::cerr << "visualVectors resized to:" << visualVectors.size() << ", " << visualVectors[visualVectors.size()].size() << std::endl;
	for (int i = 0; i < visualVectors.size(); i++) {
		std::cerr << visualVectors.size() << ", " << visualVectors[i].size() << std::endl;
	}
	auto windowSize = window->getSize();
	std::cerr << visualVectors.size();
	auto gridrow = grid.begin();
	int x = 0;
	int y = 0;
	for (auto row = visualVectors.begin(); row != visualVectors.end(); row++) {
		auto gridcol = gridrow->begin();
		for (auto col = row->begin(); col != row->end(); col++) {
			
			col->setSize(sf::Vector2f(20, 3));
			col->setOrigin(sf::Vector2f(0, col->getSize().y / 2));
			col->setFillColor(sf::Color::White);
			col->setPosition(sf::Vector2f((float)x * windowSize.x/nx,(float) y * windowSize.y/ny));
			col->setRotation(grid[x][y].second);
				//std::cerr << x << ", " << y << std::endl;
				//visualVectors[x][y].setPosition(sf::Vector2f(grid[x][y].first.x * windowSize.x, grid[x][y].first.y * windowSize.y));
				//visualVectors[x][y].setRotation(grid[x][y].second);
			gridcol++;
			y++;
		}
		y = 0;
		gridrow++;
		x++;
	}
}
