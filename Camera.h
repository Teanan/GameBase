#ifndef CAMERA_H
#define CAMERA_H

#include<SFML/Graphics.hpp>

class Camera
{
	public:
		Camera();
		~Camera();

		void initialize();
		void updateX(int x);
		void updateY(int y);
		void update();
		void draw(sf::RenderWindow &Window);

		void setView(sf::View CameraPosition);
		sf::View getView();

	private:
		sf::View m_cameraPosition;
		float m_cameraX, m_cameraY;
};

#endif // CAMERA_H