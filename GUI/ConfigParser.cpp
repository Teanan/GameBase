#include "ConfigParser.h"
#include "Button.h"
#include "ImageWidget.h"
#include "Textbox.h"
#include "Label.h"

#include "../../server/GameAssets/GraphicsManager.h"
#include "../../server/GameAssets/Graphic.h"

#include "../../libs/yaml-cpp/include/yaml-cpp/yaml.h"

void GuiConfigParser::import(Button* widget, const YAML::Node& node, GraphicsManager* graphics){
	if (node.FindValue("config") == 0) return;
	const YAML::Node& config = (*node.FindValue("config"))[0];
	
	importGlobal(widget, node, graphics);
	importTextWidget(widget, node, graphics);

	if (config.FindValue("texture") != 0)
		if (graphics->get(config.FindValue("texture")->to<sf::Uint32>()).get() != 0)
			widget->setTexture(graphics->get(config.FindValue("texture")->to<sf::Uint32>())->getTexture());
}

void GuiConfigParser::import(ImageWidget* widget, const YAML::Node& node, GraphicsManager* graphics){
	if (node.FindValue("config") == 0) return;
	const YAML::Node& config = (*node.FindValue("config"))[0];
	
	importGlobal(widget, node, graphics);

	if (config.FindValue("texture") != 0)
		if (graphics->get(config.FindValue("texture")->to<sf::Uint32>()).get() != 0)
			widget->setTexture(graphics->get(config.FindValue("texture")->to<sf::Uint32>())->getTexture());
}

void GuiConfigParser::import(Label* widget, const YAML::Node& node, GraphicsManager* graphics){
	if (node.FindValue("config") == 0) return;
	const YAML::Node& config = (*node.FindValue("config"))[0];
	
	importGlobal(widget, node, graphics);
	importTextWidget(widget, node, graphics);
}

void GuiConfigParser::import(Textbox* widget, const YAML::Node& node, GraphicsManager* graphics){
	if (node.FindValue("config") == 0) return;
	const YAML::Node& config = (*node.FindValue("config"))[0];
	
	importGlobal(widget, node, graphics);
	importTextWidget(widget, node, graphics);

	if (config.FindValue("texture") != 0)
		if (graphics->get(config.FindValue("texture")->to<sf::Uint32>()).get() != 0)
			widget->setTexture(graphics->get(config.FindValue("texture")->to<sf::Uint32>())->getTexture());
}

void GuiConfigParser::importGlobal(Widget* widget, const YAML::Node& node, GraphicsManager* graphics){
	if (node.FindValue("config") == 0) return;
	const YAML::Node& config = (*node.FindValue("config"))[0];
	
	if (config.FindValue("position") != 0)
		if (config.FindValue("position")->size() == 2)
			widget->setPosition(sf::Vector2f((*config.FindValue("position"))[0].to<float>(), (*config.FindValue("position"))[1].to<float>()));

	if (config.FindValue("size") != 0)
		if (config.FindValue("position")->size() == 2)
			widget->setSize(sf::Vector2f((*config.FindValue("size"))[0].to<float>(), (*config.FindValue("size"))[1].to<float>()));

	if (config.FindValue("originBehaviour") != 0)
		widget->setOriginBehaviour(GUIObject::originBehaviourFromString(config.FindValue("originBehaviour")->to<std::string>()));
}

void GuiConfigParser::importTextWidget(TextWidget* widget, const YAML::Node& node, GraphicsManager* graphics){
	if (node.FindValue("config") == 0) return;
	const YAML::Node& config = (*node.FindValue("config"))[0];
	
	if (config.FindValue("text") != 0)
		widget->setText(config.FindValue("text")->to<std::string>());
	
	if (config.FindValue("textSize") != 0)
		widget->setTextSize(config.FindValue("textSize")->to<sf::Uint32>());

	if (config.FindValue("textColor") != 0)
		if (config.FindValue("textColor")->size() == 4)
			widget->setTextColor(sf::Color((*config.FindValue("textColor"))[0].to<sf::Uint32>(),
										   (*config.FindValue("textColor"))[1].to<sf::Uint32>(),
										   (*config.FindValue("textColor"))[2].to<sf::Uint32>(),
										   (*config.FindValue("textColor"))[3].to<sf::Uint32>()));
		else if (config.FindValue("textColor")->size() == 3)
			widget->setTextColor(sf::Color((*config.FindValue("textColor"))[0].to<sf::Uint32>(),
										   (*config.FindValue("textColor"))[1].to<sf::Uint32>(),
										   (*config.FindValue("textColor"))[2].to<sf::Uint32>()));
	// todo : font

	if (config.FindValue("textAlignment") != 0)
		widget->setTextAlignment(TextWidget::textAlignmentFromString(config.FindValue("textAlignment")->to<std::string>()));
}