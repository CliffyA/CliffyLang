<?php
	class ThirdParty_Config extends Project_Config
	{
		public function __construct($sAction)
		{
			parent::__construct($sAction);

			$this->m_xFileArray = ProjectGen_ParseDirectory(dirname(__FILE__), "/\.h|\.c|\.cpp$/");

			if ($this->m_sAction == ACTION_EMSCRIPTEN_GMAKE)
			{
				$i = 0;
				while ($i < count($this->m_xFileArray))
				{
					$xFile = $this->m_xFileArray[$i];
					if ($xFile["sType"] == FILE_TYPE_DIRECTORY && $xFile["sName"] == "mbedtls")
					{
						array_splice($this->m_xFileArray, $i, 1);
						continue;
					}
					$i++;
				}

				//$this->m_xFileArray = array_filter($this->m_xFileArray, function($e) { var_dump($e); return strpos($e["sPath"], "mbedtls") === true; });
			}
		}

		public function GetName() { return "ThirdParty"; }
		public function GetKind() { return KIND_STATIC_LIBRARY; }
		public function GetBaseDirectory() { return dirname(__FILE__); }

		public function GetBuildOptionArray($sConfiguration, $sArchitecture)
		{
			$sArray = array();

			if ($this->m_sAction == ACTION_OSX_GMAKE || $this->m_sAction == ACTION_LINUX_GMAKE || $this->m_sAction == ACTION_EMSCRIPTEN_GMAKE)
			{
				$sArray = array_merge($sArray, array(
					"-Wno-unused-result",
					//"-std=c89",
					//"-Werror",
					//"-Wall",
					//"-Wextra",
					"-Wno-pointer-bool-conversion"
				));
			}

			return $sArray;
		}

		public function GetDependancyArray()
		{
			$sArray = array();

			if ($this->m_sAction == ACTION_IOS_XCODE)
			{
				$sArray[] = "/usr/lib/libstdc++.tbd"; // c++ supporto
			}
			
			return $sArray;
		}
		

	}
?>
