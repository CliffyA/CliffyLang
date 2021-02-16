<?php
	class Executable_Config extends Project_Config
	{
		public function __construct($sAction)
		{
			parent::__construct($sAction);

			$this->m_xFileArray = ProjectGen_ParseDirectory(dirname(__FILE__), "/\.h|\.c/");
//			$this->m_xAssetArray = ProjectGen_ParseDirectory(dirname(__FILE__) . "/../../Assets", "/\.bin$|\.ttf$|\.xm$|\.binsfx$/");
		}

		public function GetName() { return "Executable"; }
		public function GetKind() { return KIND_CONSOLE_APP; }
		public function GetBaseDirectory() { return dirname(__FILE__); }
		//public function GetLocation() { return "..\\" . $this->GetName() . "\\" . $this->m_sAction . "\\"; }

		public function GetBundleIdentifier() { return "com.numbatlogic.cliffyc"; }

//		public function GetIcon() { return dirname(__FILE__) . "/../../Svg/Logo/AppIcon.svg"; }
//		public function GetIconMask() { return dirname(__FILE__) . "/../../Svg/Logo/AppIcon_Mask.svg"; }
//		public function GetFriendlyName() { return "Creature Sweeper"; }

		public function GetIncludeDirectoryArray($sConfiguration, $sArchitecture)
		{
			$sArray = array(
				"../Core",
			//	"../Engine",
			//	"../ThirdParty",
			);

		//	if ($this->m_sAction == ACTION_OSX_GMAKE)
		//		$sArray[] = "/usr/local/opt/curl/include"; // brew install curl

			// for framebuffer hax
			/*if ($this->m_sPlatform == PLATFORM_WINDOWS)
			{
				$sArray[] = "../../../Library/Windows/GLEW/include";
				$sArray[] = "../../../Library/Windows/GLFW/include";
				//$sArray[] = "../../../Library/Windows/libcurl/include";
			}*/

			return $sArray;
		}

		public function GetLinkFlags($sConfiguration, $sArchitecture)
		{
			if ($this->m_sAction == ACTION_OSX_GMAKE)
				return "-framework OpenGL -framework AudioUnit -framework CoreAudio -framework AudioToolbox -framework CoreFoundation -framework ApplicationServices -framework IOKit -framework AppKit"; // -L/usr/local/lib -L/usr/local/opt/curl/lib 
			return "";
		}

		public function GetDependancyArray()
		{
			$sArray = array(
			//	"ThirdParty",
			//	"Engine",
			//	"EngineJob",
				"Core",
			);

			/*if ($this->m_sAction == ACTION_EMSCRIPTEN)
			{
				//$sArray = array_merge($sArray, array(
				//	"-lglfw",
				//));
			}
			else
			{
				if ($this->m_sPlatform == PLATFORM_WINDOWS)
				{
					$sArray[] = "..\..\..\Library\Windows\GLEW\lib\glew32.lib";
					$sArray[] = "..\..\..\Library\Windows\GLFW\lib-msvc90\GLFW.lib";
					$sArray[] = "opengl32.lib";
					$sArray[] = "glu32.lib";
					$sArray[] = "Ws2_32.lib";
					$sArray[] = "..\..\..\Library\Windows\libcurl\lib\dll-release\libcurl.lib";
				}

				if ($this->m_sPlatform == PLATFORM_OSX)
				{
					$sArray = array_merge($sArray, array(
						"/usr/local/lib/libGLEW.dylib",
						"/usr/local/lib/libGLFW.dylib",
						"/usr/lib/libcurl.dylib",
					));
				}
			}*/

			return $sArray;
		}

		public function GetPostBuildCommandArray($sConfiguration, $sArchitecture)
		{
			$sArray = array();

			if ($this->m_sAction == ACTION_WINDOWS_VS2008)
			{
				$sArray[] = "copy ..\\..\\..\\..\\Library\\Windows\\GLEW\\bin\\glew32.dll ..\\..\\..\\..\\Bin";
				$sArray[] = "copy ..\\..\\..\\..\\Library\\Windows\\libcurl\\lib\\dll-release\\libcurl.dll ..\\..\\..\\..\\Bin";
			}

			return $sArray;
		}
	}
?>
