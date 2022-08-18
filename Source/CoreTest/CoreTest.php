<?php
	class CoreTest_Config extends Project_Config
	{
		public function __construct($sAction)
		{
			parent::__construct($sAction);

			$this->m_xFileArray = ProjectGen_ParseDirectory(dirname(__FILE__), "/\.h|\.c/");
		}

		public function GetName() { return "CoreTest"; }
		public function GetKind() { return KIND_CONSOLE_APP; }
		public function GetBaseDirectory() { return dirname(__FILE__); }

		public function GetIncludeDirectoryArray($sConfiguration, $sArchitecture)
		{
			return array(
				"../Core",
				"../Engine",
			//	"../ThirdParty",
			);
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
				"Core",
				"Engine",
			//	"EngineJob",
				//"ThirdParty",
			);

			/*if ($this->m_sPlatform == PLATFORM_OSX)
			{
				$sArray = array_merge($sArray, array(
					//"/usr/local/lib/libGLEW.dylib",
					//"/usr/local/lib/libGLFW.dylib",
					"/usr/lib/libcurl.dylib",
				));
			}*/

			return $sArray;
		}

		/*public function GetPostBuildCommandArray($sConfiguration, $sArchitecture)
		{
			$sArray = array();

			if ($this->m_sAction == ACTION_WINDOWS_VS2008)
			{
				//$sArray[] = "copy ..\\..\\..\\Library\\Windows\\GLEW\\bin\\glew32.dll ..\\..\\..\\Bin";
				//$sArray[] = "copy ..\\..\\..\\Library\\Windows\\libcurl\\lib\\dll-release\\libcurl.dll ..\\..\\..\\Bin";
				$sArray[] = "cd ..";
				$sArray[] = "cd ..";
				$sArray[] = "cd ..";
				$sArray[] = "cd ..";
				$sArray[] = "cd Bin";
				$sArray[] = "CoreTest.exe";
			}

			return $sArray;
		}*/
	}
?>
