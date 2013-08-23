#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include "GameState.h"
#include "InGame.h"
#include "Config.h"
#include "UserEventsHandler.h"
#include "WorldRenderer.h"

#include "../server/GameAssets/GraphicsManager.h"
#include "../server/GameAssets/Graphic.h"

#include "GUI/Button.h"
#include "GUI/Textbox.h"
#include "GUI/ConfigParser.h"

#include <fstream>

class MainMenu: public GameState
{
	public:
	
		MainMenu(){

		};

		void init(){
			m_play = new Button;

			std::ifstream stream("data/gui.yaml");
			YAML::Parser parser(stream);
	
			YAML::Node configFile;
			while(parser.GetNextDocument(configFile)){
				for(size_t t=0; t < configFile["client"].size(); t++){
					const YAML::Node &yamlConfig(configFile["client"][t]);

					if(configFile["client"][t].FindValue("name")->to<std::string>() == "MainMenu"){

						const YAML::Node* widgets(configFile["client"][t].FindValue("widgets"));
						if (widgets == 0) break;

						for (YAML::Iterator it = widgets->begin(); it != widgets->end(); it++){
							if (it->FindValue("id")->to<std::string>() == "play_button"){
								GuiConfigParser::import(m_play, *it, Application::graphicsManager());
							}
						}
					}
				}
			}
		};

		void update(){
			m_play->update();

			if (m_play->clicked()){
				Application::instance()->setCurrentGameState(InGameState);
				//((InGame*)Application::instance()->getGameState(InGameState))->setRenderingMap();
			}
		};

		void render(sf::RenderTarget* renderTarget){
			renderTarget->draw(*m_play);
		};

	private:

		Button* m_play;
};

#endif // MAINMENU_H_INCLUDED