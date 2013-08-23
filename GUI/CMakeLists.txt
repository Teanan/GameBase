set(GUI_SOURCES
	Button.h
	ConfigParser.h
	GUICore.h
	GUIEvents.h
	GUILayer.h
	GUIObject.h
	ImageWidget.h
	Label.h
	PasswordTextbox.h
	Textbox.h
	TextWidget.h
	Widget.h
	WidgetsLayer.h

	Button.cpp
	ConfigParser.cpp
	GUICore.cpp
	GUIEvents.cpp
	GUILayer.cpp
	GUIObject.cpp
	ImageWidget.cpp
	Label.cpp
	PasswordTextbox.cpp
	Textbox.cpp
	TextWidget.cpp
	Widget.cpp
	WidgetsLayer.cpp
)

add_library(GUI ${GUI_SOURCES})