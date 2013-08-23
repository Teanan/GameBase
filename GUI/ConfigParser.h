#ifndef GUICONFIGPARSER_H_INCLUDED
#define GUICONFIGPARSER_H_INCLUDED

#include "../../libs/yaml-cpp/include/yaml-cpp/yaml.h"

class GraphicsManager;

class Widget;
class TextWidget;

class Button;
class ImageWidget;
class Label;
class Textbox;

class GuiConfigParser
{
	public:
		
		static void import(Button*, const YAML::Node&, GraphicsManager* graphics);
		static void import(ImageWidget*, const YAML::Node&, GraphicsManager* graphics);
		static void import(Label*, const YAML::Node&, GraphicsManager* graphics);
		static void import(Textbox*, const YAML::Node&, GraphicsManager* graphics);

	private:
		
		static void importGlobal(Widget*, const YAML::Node&, GraphicsManager* graphics);
		static void importTextWidget(TextWidget*, const YAML::Node&, GraphicsManager* graphics);

};

#endif // GUICONFIGPARSER_H_INCLUDED