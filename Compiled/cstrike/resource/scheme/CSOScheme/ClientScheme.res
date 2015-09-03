//
// TRACKER SCHEME RESOURCE FILE
//
// sections:
//		colors			- all the colors used by the scheme
//		basesettings	- contains settings for app to use to draw controls
//		fonts			- list of all the fonts used by app
//		borders			- description of all the borders
//
//
Scheme
{
	//Name - currently overriden in code
	//{
	//	"Name"	"ClientScheme"
	//}

	//////////////////////// COLORS ///////////////////////////
	Colors
	{
		// base colors
		"White"				"255 255 255 255"
		"OffWhite"			"216 216 216 255"
		"DullWhite"			"142 142 142 255"
		"Orange"			"255 155 0 255"
		"TransparentBlack"	"0 0 0 128"
		"Black"				"0 0 0 255"

		"Blank"				"0 0 0 0"

		"ScrollBarGrey"		"255 255 255 255"
		"ScrollBarHilight"	"110 110 110 255"
		"ScrollBarDark"		"93 93 93 255"
	}

	///////////////////// BASE SETTINGS ////////////////////////
	// default settings for all panels
	// controls use these to determine their settings
	BaseSettings
	{
		// vgui_controls color specifications
		// vgui_controls color specifications
		Border.Bright					"200 200 200 196"	// the lit side of a control
		Border.Dark						"40 40 40 196"		// the dark/unlit side of a control
		Border.Selection				"0 0 0 196"			// the additional border color for displaying the default/selected button

		Button.TextColor				"White"
		Button.BgColor					"Blank"
		Button.ArmedTextColor			"White"
		Button.ArmedBgColor				"Blank"
		Button.DepressedTextColor		"White"
		Button.DepressedBgColor			"Blank"
		Button.FocusBorderColor			"Blank"

		Button.TextInsetX			"8"
		Button.TextInsetY			"0"
		Button.SelectedInsetX			"1"
		Button.SelectedInsetY			"1"

		Button.LeftN				"resource/scheme/CSOScheme/Control/button/btn_default_left@n"
		Button.CenterN				"resource/scheme/CSOScheme/Control/button/btn_default_center@n"
		Button.RightN				"resource/scheme/CSOScheme/Control/button/btn_default_right@n" 
		Button.LeftO				"resource/scheme/CSOScheme/Control/button/btn_default_left@o"
		Button.CenterO				"resource/scheme/CSOScheme/Control/button/btn_default_center@o"
		Button.RightO				"resource/scheme/CSOScheme/Control/button/btn_default_right@o"
		Button.LeftC				"resource/scheme/CSOScheme/Control/button/btn_default_left@c"
		Button.CenterC				"resource/scheme/CSOScheme/Control/button/btn_default_center@c"
		Button.RightC				"resource/scheme/CSOScheme/Control/button/btn_default_right@c" 

		CheckButton.TextColor			"OffWhite"
		CheckButton.SelectedTextColor	"White"
		CheckButton.BgColor				"TransparentBlack"
		CheckButton.Border1  			"Border.Dark" 		// the left checkbutton border
		CheckButton.Border2  			"Border.Bright"		// the right checkbutton border
		CheckButton.Check				"White"				// color of the check itself

		CheckButton.On				"resource/scheme/CSOScheme/Control/checkbox/checkbox_on"
		CheckButton.Off				"resource/scheme/CSOScheme/Control/checkbox/checkbox_off"

		RadioButton.On				"resource/scheme/CSOScheme/Control/radiobutton/radiobutton_on"
		RadioButton.Off				"resource/scheme/CSOScheme/Control/radiobutton/radiobutton_off"

		ComboBoxButton.ArrowColor		"DullWhite"
		ComboBoxButton.ArmedArrowColor	"White"
		ComboBoxButton.BgColor			"Blank"
		ComboBoxButton.DisabledBgColor	"Blank"

		Frame.TitleTextInsetX			16
		Frame.ClientInsetX				8
		Frame.ClientInsetY				6
		Frame.BgColor					"0 0 0 0"
		Frame.OutOfFocusBgColor			"0 0 0 0"
		Frame.FocusTransitionEffectTime	"0.0"							// time it takes for a window to fade in/out on focus/out of focus
		Frame.TransitionEffectTime		"0.0"
		Frame.AutoSnapRange				"0"

		FrameGrip.Color1				"200 200 200 196"
		FrameGrip.Color2				"0 0 0 196"
		FrameTitleButton.FgColor		"200 200 200 196"
		FrameTitleButton.BgColor		"Blank"
		FrameTitleButton.DisabledFgColor	"255 255 255 192"
		FrameTitleButton.DisabledBgColor	"Blank"
		FrameSystemButton.FgColor		"Blank"
		FrameSystemButton.BgColor		"Blank"
		FrameSystemButton.Icon			""
		FrameSystemButton.DisabledIcon	""
		FrameTitleBar.Font				"UiBold"
		FrameTitleBar.Font				"DefaultLarge"
		FrameTitleBar.TextColor			"White"
		FrameTitleBar.BgColor			"Blank"
		FrameTitleBar.DisabledTextColor	"255 255 255 192"
		FrameTitleBar.DisabledBgColor	"Blank"

		Frame.TopLeft			"resource/scheme/CSOScheme/Control/igframe/window_default_top_left"
		Frame.TopCenter			"resource/scheme/CSOScheme/Control/igframe/window_default_top_center"
		Frame.TopRight			"resource/scheme/CSOScheme/Control/igframe/window_default_top_right"
		Frame.MiddleLeft			"resource/scheme/CSOScheme/Control/igframe/window_default_center_left"
		Frame.MiddleCenter			"resource/scheme/CSOScheme/Control/igframe/window_default_center_center"
		Frame.MiddleRight			"resource/scheme/CSOScheme/Control/igframe/window_default_center_right"
		Frame.BottomLeft			"resource/scheme/CSOScheme/Control/igframe/window_default_bottom_left"
		Frame.BottomCenter			"resource/scheme/CSOScheme/Control/igframe/window_default_bottom_center"
		Frame.BottomRight			"resource/scheme/CSOScheme/Control/igframe/window_default_bottom_Right"

		GraphPanel.FgColor				"White"
		GraphPanel.BgColor				"TransparentBlack"

		Label.TextDullColor				"DullWhite"
		Label.TextColor					"OffWhite"
		Label.TextBrightColor			"White"
		Label.SelectedTextColor			"White"
		Label.BgColor					"Blank"
		Label.DisabledFgColor1			"117 117 117 255"
		Label.DisabledFgColor2			"30 30 30 255"

		ListPanel.ColumnHeaderLeftN			"resource/scheme/CSOScheme/Control/listpanel/column_left_n"
		ListPanel.ColumnHeaderCenterN			"resource/scheme/CSOScheme/Control/listpanel/column_center_n"
		ListPanel.ColumnHeaderRightN			"resource/scheme/CSOScheme/Control/listpanel/column_right_n"
		ListPanel.ColumnHeaderLeftO			"resource/scheme/CSOScheme/Control/listpanel/column_left_o"
		ListPanel.ColumnHeaderCenterO			"resource/scheme/CSOScheme/Control/listpanel/column_center_o"
		ListPanel.ColumnHeaderRightO			"resource/scheme/CSOScheme/Control/listpanel/column_right_o"
		ListPanel.ColumnHeaderLeftC			"resource/scheme/CSOScheme/Control/listpanel/column_left_c"
		ListPanel.ColumnHeaderCenterC			"resource/scheme/CSOScheme/Control/listpanel/column_center_c"
		ListPanel.ColumnHeaderRightC			"resource/scheme/CSOScheme/Control/listpanel/column_right_c"
		ListPanel.TextColor					"OffWhite"
		ListPanel.TextBgColor				"Blank"
		ListPanel.BgColor					"TransparentBlack"
		ListPanel.SelectedTextColor			"Black"
		ListPanel.SelectedBgColor			"Orange"
		ListPanel.SelectedOutOfFocusBgColor	"255 155 0 128"
		ListPanel.EmptyListInfoTextColor	"OffWhite"

		Menu.TextColor					"Black"
		Menu.BgColor					"Blank"
		Menu.ArmedTextColor				"Black"
		Menu.ArmedBgColor				"Orange"
		Menu.TextInset					"6"

		Menu.TopLeft			"resource/scheme/CSOScheme/Control/textentry/Input_default_top_left@n"
		Menu.TopCenter			"resource/scheme/CSOScheme/Control/textentry/Input_default_top_center@n"
		Menu.TopRight			"resource/scheme/CSOScheme/Control/textentry/Input_default_top_right@n"
		Menu.MiddleLeft			"resource/scheme/CSOScheme/Control/textentry/Input_default_center_left@n"
		Menu.MiddleCenter			"resource/scheme/CSOScheme/Control/textentry/Input_default_center_center@n"
		Menu.MiddleRight			"resource/scheme/CSOScheme/Control/textentry/Input_default_center_right@n"
		Menu.BottomLeft			"resource/scheme/CSOScheme/Control/textentry/Input_default_bottom_left@n"
		Menu.BottomCenter			"resource/scheme/CSOScheme/Control/textentry/Input_default_bottom_center@n"
		Menu.BottomRight			"resource/scheme/CSOScheme/Control/textentry/Input_default_bottom_Right@n"

		Chat.TypingText					"Black"

		Panel.FgColor					"DullWhite"
		Panel.BgColor					"Blank"

		HTML.BgColor					"Black"

		BuyPreset.BgColor				"0 0 0 128"
		BuyPresetListBox.BgColor			"0 0 0 128"
		"Popup.BgColor"					"0 0 0 230"

		ProgressBar.FgColor				"White"
		ProgressBar.BgColor				"TransparentBlack"

		PropertySheet.TextColor			"OffWhite"
		PropertySheet.SelectedTextColor	"White"
		PropertySheet.TransitionEffectTime	"0.25"	// time to change from one tab to another

		PropertySheet.TopLeft			"resource/scheme/CSOScheme/Control/frame_dehilight/window_default_top_left"
		PropertySheet.TopCenter			"resource/scheme/CSOScheme/Control/frame_dehilight/window_default_top_center"
		PropertySheet.TopRight			"resource/scheme/CSOScheme/Control/frame_dehilight/window_default_top_right"
		PropertySheet.MiddleLeft			"resource/scheme/CSOScheme/Control/frame_dehilight/window_default_center_left"
		PropertySheet.MiddleCenter			"resource/scheme/CSOScheme/Control/frame_dehilight/window_default_center_center"
		PropertySheet.MiddleRight			"resource/scheme/CSOScheme/Control/frame_dehilight/window_default_center_right"
		PropertySheet.BottomLeft			"resource/scheme/CSOScheme/Control/frame_dehilight/window_default_bottom_left"
		PropertySheet.BottomCenter			"resource/scheme/CSOScheme/Control/frame_dehilight/window_default_bottom_center"
		PropertySheet.BottomRight			"resource/scheme/CSOScheme/Control/frame_dehilight/window_default_bottom_Right"

		PropertyTab.LeftN			"resource/scheme/CSOScheme/Control/tabbutton/tab_big_abled_left_n"
		PropertyTab.CenterN			"resource/scheme/CSOScheme/Control/tabbutton/tab_big_abled_center_n"
		PropertyTab.RightN			"resource/scheme/CSOScheme/Control/tabbutton/tab_big_abled_right_n" 
		PropertyTab.LeftO			"resource/scheme/CSOScheme/Control/tabbutton/tab_big_abled_left_o"
		PropertyTab.CenterO			"resource/scheme/CSOScheme/Control/tabbutton/tab_big_abled_center_o"
		PropertyTab.RightO			"resource/scheme/CSOScheme/Control/tabbutton/tab_big_abled_right_o" 
		PropertyTab.LeftC			"resource/scheme/CSOScheme/Control/tabbutton/tab_big_abled_left_c"
		PropertyTab.CenterC			"resource/scheme/CSOScheme/Control/tabbutton/tab_big_abled_center_c"
		PropertyTab.RightC			"resource/scheme/CSOScheme/Control/tabbutton/tab_big_abled_right_c"

		RadioButton.TextColor			"DullWhite"
		RadioButton.SelectedTextColor	"White"

		RichText.TextColor				"OffWhite"
		RichText.BgColor				"TransparentBlack"
		RichText.SelectedTextColor		"Black"
		RichText.SelectedBgColor		"Orange"

		ScrollBar.Wide					10
	  	ScrollBarNobBorder.Outer 			"ScrollBarDark"
		ScrollBarNobBorder.Inner 			"ScrollBarGrey"
		ScrollBarNobBorderHover.Inner 			"ScrollBarGrey"
		ScrollBarNobBorderDragging.Inner 		"ScrollBarHilight"

		ScrollBarButton.FgColor				"ScrollBarHilight"
		ScrollBarButton.BgColor				"ScrollBarGrey"
		ScrollBarButton.ArmedFgColor			"ScrollBarHilight"
		ScrollBarButton.ArmedBgColor			"ScrollBarGrey"
		ScrollBarButton.DepressedFgColor		"ScrollBarHilight"
		ScrollBarButton.DepressedBgColor		"ScrollBarGrey"

		ScrollBarSlider.Inset				1			// Number of pixels to inset scroll bar nob
		ScrollBarSlider.FgColor				"White"			// nob color
		ScrollBarSlider.BgColor				"Black"	// slider background color
		ScrollBarSlider.NobFocusColor			"ScrollBarHilight"		// nob mouseover color
		ScrollBarSlider.NobDragColor			"ScrollBarHilight"		// nob active drag color

		ScrollBarSlider.ButtonScrollUpN			"resource/scheme/CSOScheme/Control/scrollbar/btn_default_scroll_up@n"
		ScrollBarSlider.ButtonScrollUpO			"resource/scheme/CSOScheme/Control/scrollbar/btn_default_scroll_up@o"
		ScrollBarSlider.ButtonScrollUpC			"resource/scheme/CSOScheme/Control/scrollbar/btn_default_scroll_up@c"
		ScrollBarSlider.ButtonScrollDownN			"resource/scheme/CSOScheme/Control/scrollbar/btn_default_scroll_down@n"
		ScrollBarSlider.ButtonScrollDownO			"resource/scheme/CSOScheme/Control/scrollbar/btn_default_scroll_down@o"
		ScrollBarSlider.ButtonScrollDownC			"resource/scheme/CSOScheme/Control/scrollbar/btn_default_scroll_down@c"
		ScrollBarSlider.VerticalTopImg			"resource/scheme/CSOScheme/Control/scrollbar/btn_default_scroll_bar_top@n"
		ScrollBarSlider.VerticalMiddleImg			"resource/scheme/CSOScheme/Control/scrollbar/btn_default_scroll_bar_center@n"
		ScrollBarSlider.VerticalBottomImg			"resource/scheme/CSOScheme/Control/scrollbar/btn_default_scroll_bar_bottom@n"

		SectionedListPanel.HeaderTextColor	"Orange"
		SectionedListPanel.HeaderBgColor	"Blank"
		SectionedListPanel.DividerColor		"Orange"
		SectionedListPanel.TextColor		"DullWhite"
		SectionedListPanel.BrightTextColor	"White"
		SectionedListPanel.BgColor			"TransparentBlack"
		SectionedListPanel.SelectedTextColor			"Black"
		SectionedListPanel.SelectedBgColor				"Orange"
		SectionedListPanel.OutOfFocusSelectedTextColor	"Black"
		SectionedListPanel.OutOfFocusSelectedBgColor	"255 155 0 128"

		Slider.NobColor				"108 108 108 255"
		Slider.NobFocusColor			"Orange"
		Slider.TextColor			"180 180 180 255"
		Slider.TrackColor			"31 31 31 255"
		Slider.DisabledTextColor1	"117 117 117 255"
		Slider.DisabledTextColor2	"30 30 30 255"

		TextEntry.TextColor			"Black"
		TextEntry.BgColor			"TransparentBlack"
		TextEntry.CursorColor		"Black"
		TextEntry.DisabledTextColor	"DullWhite"
		TextEntry.DisabledBgColor	"Blank"
		TextEntry.SelectedTextColor	"Black"
		TextEntry.SelectedBgColor	"Orange"
		TextEntry.OutOfFocusSelectedBgColor	"255 155 0 128"
		TextEntry.FocusEdgeColor	"0 0 0 196"
		TextEntry.CmpositionBgColor	"200 200 200 92"

		TextEntry.TopLeft			"resource/scheme/CSOScheme/Control/textentry/Input_default_top_left@n"
		TextEntry.TopCenter			"resource/scheme/CSOScheme/Control/textentry/Input_default_top_center@n"
		TextEntry.TopRight			"resource/scheme/CSOScheme/Control/textentry/Input_default_top_right@n"
		TextEntry.MiddleLeft			"resource/scheme/CSOScheme/Control/textentry/Input_default_center_left@n"
		TextEntry.MiddleCenter			"resource/scheme/CSOScheme/Control/textentry/Input_default_center_center@n"
		TextEntry.MiddleRight			"resource/scheme/CSOScheme/Control/textentry/Input_default_center_right@n"
		TextEntry.BottomLeft			"resource/scheme/CSOScheme/Control/textentry/Input_default_bottom_left@n"
		TextEntry.BottomCenter			"resource/scheme/CSOScheme/Control/textentry/Input_default_bottom_center@n"
		TextEntry.BottomRight			"resource/scheme/CSOScheme/Control/textentry/Input_default_bottom_Right@n"

		ToggleButton.SelectedTextColor	"White"

		Tooltip.TextColor			"0 0 0 196"
		Tooltip.BgColor				"Orange"

		TreeView.BgColor			"TransparentBlack"

		WizardSubPanel.BgColor		"Blank"

		// scheme-specific colors
		"FgColor"		"Orange"
		"BgColor"		"TransparentBlack"

		"ViewportBG"		"Blank"
		"team0"			"204 204 204 255" // Spectators
		"team1"			"255 64 64 255" // CT's
		"team2"			"153 204 255 255" // T's

		"MapDescriptionText"	"White" // the text used in the map description window
		"CT_Blue"			"153 204 255 255"
		"T_Red"				"255 64 64 255"
		"Hostage_Yellow"	"Panel.FgColor"
		"HudIcon_Green"		"0 160 0 255"
		"HudIcon_Red"		"160 0 0 255"

		// CHudMenu
		"ItemColor"		"255 167 42 200"	// default 255 167 42 255
		"MenuColor"		"233 208 173 255"
		"MenuBoxBg"		"0 0 0 100"

		// weapon selection colors
		"SelectionNumberFg"		"255 220 0 200"
		"SelectionTextFg"		"255 220 0 200"
		"SelectionEmptyBoxBg" 	"0 0 0 80"
		"SelectionBoxBg" 		"0 0 0 80"
		"SelectionSelectedBoxBg" "0 0 0 190"

		// Hint message colors
		"HintMessageFg"			"255 255 255 255"
		"HintMessageBg" 		"0 0 0 60"

		"ProgressBarFg"			"255 30 13 255"

		// Top-left corner of the "Counter-Strike" on the main screen
		"Main.Title1.X"		"32"
		"Main.Title1.Y"		"180"
		"Main.Title1.Color"	"255 255 255 255"

		// Top-left corner of the "SOURCE" on the main screen
		"Main.Title2.X"		"380"
		"Main.Title2.Y"		"205"
		"Main.Title2.Color"	"255 255 255 80"

		// Top-left corner of the "BETA" on the main screen
		"Main.Title3.X"		"460"
		"Main.Title3.Y"		"-10"
		"Main.Title3.Color"	"255 255 0 255"

		// Top-left corner of the menu on the main screen
		"Main.Menu.X"		"32"
		"Main.Menu.Y"		"248"

		// Blank space to leave beneath the menu on the main screen
		"Main.BottomBorder"	"32"

		// MouseOverPanelButton control settings
		"MouseOverPanelButton.Keyboard"		"resource/scheme/CSOScheme/Control/button_ingame/keyboard"
		"MouseOverPanelButton.BlankSlot"	"resource/scheme/CSOScheme/Control/buybutton/blank_slot"
		"MouseOverPanelButton.Select"		"resource/scheme/CSOScheme/Control/buybutton/select"
		"MouseOverPanelButton.KeyboardOffset"	"3"
		"MouseOverPanelButton.KeyboardSize"	"18"

		// BuyMouseOverPanelButton control settings
		"BuyMouseOverPanelButton.Keyboard"		"resource/scheme/CSOScheme/Control/button_ingame/keyboard"
		"BuyMouseOverPanelButton.BlankSlot"		"resource/scheme/CSOScheme/Control/buybutton/blank_slot"
		"BuyMouseOverPanelButton.Select"		"resource/scheme/CSOScheme/Control/buybutton/select"
		"BuyMouseOverPanelButton.PanelBG"		"resource/scheme/CSOScheme/Control/basket/basket_blank_slot"
		"BuyMouseOverPanelButton.KeyboardOffset"	"3"
		"BuyMouseOverPanelButton.KeyboardSize"		"18"

		// BuyPresetButton control settings
		"BuyPresetButton.Keyboard"		"resource/scheme/CSOScheme/Control/button_ingame/keyboard"
		"BuyPresetButton.BlankSlot"		"resource/scheme/CSOScheme/Control/button_ingame/favoritebg"
		"BuyPresetButton.Select"		"resource/scheme/CSOScheme/Control/buybutton/select"
		"BuyPresetButton.KeyboardOffset"	"6"
		"BuyPresetButton.KeyboardSize"		"18"
	}

	//
	//////////////////////// FONTS /////////////////////////////
	//
	// describes all the fonts
	Fonts
	{
		// fonts are used in order that they are listed
		// fonts listed later in the order will only be used if they fulfill a range not already filled
		// if a font fails to load then the subsequent fonts will replace
		"Default"
		{
			"1"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"12"
				"weight"	"0"
				"yres"	"480 599"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"2"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"13"
				"weight"	"0"
				"yres"	"600 767"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"3"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"14"
				"weight"	"0"
				"yres"	"768 1023"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"4"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"22"
				"weight"	"0"
				"yres"	"1024 1199"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"5"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"24"
				"weight"	"0"
				"yres"	"1200 6000"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"6"
			{
				"name"		"Verdana"
				"tall"		"12"
				"range" 		"0x0000 0x00FF"
				"weight"		"900"
			}
			"7"
			{
				"name"		"Aria"
				"tall"		"12"
				"range" 		"0x0000 0x00FF"
				"weight"		"800"
			}
		}
		"DefaultUnderline"
		{
			"1"
			{
				"name"		"Tahoma"
				"tall"		"12"
				"weight"	"500"
				"underline" "1"
				"range"		"0x0000 0x017F" //	Basic Latin, Latin-1 Supplement, Latin Extended-A
			}
			"2"
			{
				"name"		"Arial"
				"tall"		"11"
				"range" 		"0x0000 0x00FF"
				"weight"		"800"
			}
		}
		"DefaultSmall"
		{
			"1"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"12"
				"weight"	"0"
				"yres"	"480 599"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"2"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"13"
				"weight"	"0"
				"yres"	"600 767"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"3"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"14"
				"weight"	"0"
				"yres"	"768 1023"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"4"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"22"
				"weight"	"0"
				"yres"	"1024 1199"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"5"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"24"
				"weight"	"0"
				"yres"	"1200 6000"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"6"
			{
				"name"		"Verdana"
				"tall"		"12"
				"range" 		"0x0000 0x00FF"
				"weight"		"900"
			}
			"7"
			{
				"name"		"Aria"
				"tall"		"12"
				"range" 		"0x0000 0x00FF"
				"weight"		"800"
			}
		}
		"DefaultVerySmall"
		{
			"1"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"12"
				"weight"	"0"
				"yres"	"480 599"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"2"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"13"
				"weight"	"0"
				"yres"	"600 767"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"3"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"14"
				"weight"	"0"
				"yres"	"768 1023"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"4"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"22"
				"weight"	"0"
				"yres"	"1024 1199"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"5"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"24"
				"weight"	"0"
				"yres"	"1200 6000"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"6"
			{
				"name"		"Verdana"
				"tall"		"12"
				"range" 		"0x0000 0x00FF"
				"weight"		"900"
			}
			"7"
			{
				"name"		"Aria"
				"tall"		"12"
				"range" 		"0x0000 0x00FF"
				"weight"		"800"
			}
		}
		// Used by scoreboard and spectator UI for names which don't map in the normal fashion
		"DefaultVerySmallFallBack"
		{
			"1"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"11"
				"weight"	"0"
				"yres"	"480 599"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"2"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"12"
				"weight"	"0"
				"yres"	"600 767"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"3"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"13"
				"weight"	"0"
				"yres"	"768 1023"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"4"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"21"
				"weight"	"0"
				"yres"	"1024 1199"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"5"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"23"
				"weight"	"0"
				"yres"	"1200 6000"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"6"
			{
				"name"		"Verdana"
				"tall"		"11"
				"range" 		"0x0000 0x00FF"
				"weight"		"800"
			}
			"7"
			{
				"name"		"Aria"
				"tall"		"11"
				"range" 		"0x0000 0x00FF"
				"weight"		"700"
			}
		}

		// this is the symbol font
		"Marlett"
		{
			"1"
			{
				"name"		"Marlett"
				"tall"		"9"
				"weight"	"0"
				"symbol"	"1"
				"range"		"0x0000 0x007F"	//	Basic Latin
			}
		}

		"MenuTitle"
		{
			"1"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"12"
				"weight"	"0"
				"unlimited"	"1"
				"freetype"	"1"
			}
		}

		"ChatFont"
		{
			"1"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"14"
				"weight"	"0"
				"yres"	"480 599"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"2"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"15"
				"weight"	"0"
				"yres"	"600 767"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"3"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"16"
				"weight"	"0"
				"yres"	"768 1023"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"4"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"22"
				"weight"	"0"
				"yres"	"1024 1199"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"5"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"24"
				"weight"	"0"
				"yres"	"1200 10000"
				"unlimited"	"1"
				"freetype"	"1"
			}
		}

		"ChatHistoryFont"
		{
			"1"
			{
				"name"		"Verdana"
				"tall"		"12"
				"weight"	"700"
				"yres"	"480 599"
				"dropshadow"	"1"
			}
			"2"
			{
				"name"		"Verdana"
				"tall"		"13"
				"weight"	"700"
				"yres"	"600 767"
				"dropshadow"	"1"
			}
			"3"
			{
				"name"		"Verdana"
				"tall"		"14"
				"weight"	"700"
				"yres"	"768 1023"
				"dropshadow"	"1"
			}
			"4"
			{
				"name"		"Verdana"
				"tall"		"20"
				"weight"	"700"
				"yres"	"1024 1199"
				"dropshadow"	"1"
			}
			"5"
			{
				"name"		"Verdana"
				"tall"		"24"
				"weight"	"700"
				"yres"	"1200 10000"
				"dropshadow"	"1"
			}
		}

		"CreditsText"
		{
			"1"
			{
				"name"		"Verdana"
				"tall"		"12"
				"weight"	"700"
				"yres"	"480 599"
			}
			"2"
			{
				"name"		"Verdana"
				"tall"		"13"
				"weight"	"700"
				"yres"	"600 767"
			}
			"3"
			{
				"name"		"Verdana"
				"tall"		"14"
				"weight"	"700"
				"yres"	"768 1023"
			}
			"4"
			{
				"name"		"Verdana"
				"tall"		"20"
				"weight"	"700"
				"yres"	"1024 1199"
			}
			"5"
			{
				"name"		"Verdana"
				"tall"		"24"
				"weight"	"700"
				"yres"	"1200 10000"
			}
		}

		"ScoreboardHeader"
		{
			"1"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"12"
				"weight"	"0"
				"unlimited"	"1"
				"freetype"	"1"
			}
		}

		"ScoreboardTeamName"
		{
			"1"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"14"
				"weight"	"0"
				"unlimited"	"1"
				"freetype"	"1"
			}
		}

		"ScoreboardScore"
		{
			"1"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"45"
				"weight"	"0"
				"unlimited"	"1"
				"freetype"	"1"
			}
		}

		"ScoreboardColumns"
		{
			"1"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"12"
				"weight"	"0"
				"yres"	"480 599"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"2"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"13"
				"weight"	"0"
				"yres"	"600 767"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"3"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"14"
				"weight"	"0"
				"yres"	"768 1023"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"4"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"22"
				"weight"	"0"
				"yres"	"1024 1199"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"5"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"24"
				"weight"	"0"
				"yres"	"1200 6000"
				"unlimited"	"1"
				"freetype"	"1"
			}
			"6"
			{
				"name"		"Verdana"
				"tall"		"12"
				"range" 		"0x0000 0x00FF"
				"weight"		"900"
			}
			"7"
			{
				"name"		"Aria"
				"tall"		"12"
				"range" 		"0x0000 0x00FF"
				"weight"		"800"
			}
		}
		
		"ScoreboardPlayersAlive"
		{
			"1"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"12"
				"weight"	"0"
				"unlimited"	"1"
				"freetype"	"1"
			}
		}
		
		"ScoreboardPlayersAliveSuffix"
		{
			"1"
			{
				"name"		"resource/scheme/CSOScheme/Font/segoeui.ttf"
				"tall"		"10"
				"weight"	"0"
				"unlimited"	"1"
				"freetype"	"1"
			}
		}
	}

	//
	//////////////////// BORDERS //////////////////////////////
	//
	// describes all the border types
	Borders
	{
		BaseBorder
		{
			"backgroundtype" "2"
		}
		
		TitleButtonBorder
		{
			"backgroundtype" "2"
		}

		TitleButtonDisabledBorder
		{
			"backgroundtype" "2"
		}

		TitleButtonDepressedBorder
		{
			"backgroundtype" "2"
		}

		ScrollBarButtonBorder
		{
			"backgroundtype" "2"
		}

		ScrollBarButtonDepressedBorder
		{
			"backgroundtype" "2"
		}
		
		ButtonBorder
		{
			"backgroundtype" "2"
		}

		FrameBorder
		{
			"backgroundtype" "2"
		}

		TabBorder
		{
			"backgroundtype" "2"
		}

		TabActiveBorder
		{
			"backgroundtype" "2"
		}


		ToolTipBorder
		{
			"backgroundtype" "2"
		}

		// this is the border used for default buttons (the button that gets pressed when you hit enter)
		ButtonKeyFocusBorder
		{
			"backgroundtype" "2"
		}

		ButtonDepressedBorder
		{
			"backgroundtype" "2"
		}

		ComboBoxBorder
		{
			"backgroundtype" "2"
		}

		MenuBorder
		{
			"backgroundtype" "2"
		}
		BrowserBorder
		{
			"backgroundtype" "2"
		}

		BuyPresetBorder
		{
			"backgroundtype" "2"
		}

		BuyPresetButtonBorder
		{
			"backgroundtype" "2"
		}
	}

	//////////////////////// CUSTOM FONT FILES /////////////////////////////
	//
	// specifies all the custom (non-system) font files that need to be loaded to service the above described fonts
	CustomFontFiles
	{
	}
}