<?php
	class Core_Config extends Project_Config
	{	
		public function __construct($sAction)
		{
			parent::__construct($sAction);
			$this->m_xFileArray = ProjectGen_ParseDirectory(dirname(__FILE__), "/\.h|\.c/");
		}

		public function GetName() { return "Core"; }
		public function GetKind() { return KIND_STATIC_LIBRARY; }
		public function GetBaseDirectory() { return dirname(__FILE__); }

		public function GetIncludeDirectoryArray($sConfiguration, $sArchitecture)
		{
			$sArray = array(
			//	"../ThirdParty",
			//	"../Engine",
			);

			/*if ($this->m_sPlatform == PLATFORM_WINDOWS)
			{
				$sArray[] = "../../../Library/Windows/GLEW/include";
				$sArray[] = "../../../Library/Windows/GLFW/include";
				$sArray[] = "../../../Library/Windows/libcurl/include";
			}*/

			return $sArray;
		}

		public function GetDependancyArray()
		{
			$sArray = array(
				//"ThirdParty",
			//	"Engine",
			//	"Core",
			);

			return $sArray;
		}
	}
?>
