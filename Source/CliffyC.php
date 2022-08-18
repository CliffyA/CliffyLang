<?php
//	ini_set("log_errors", false);
	date_default_timezone_set("UTC");

	include_once dirname(__FILE__) . "/../../ProjectGen/ProjectGen.php";


	include_once dirname(__FILE__) . "/Engine/Engine.php";
	//include_once dirname(__FILE__) . "/EngineJob/EngineJob.php";
	//include_once dirname(__FILE__) . "/EngineTest/EngineTest.php";
	include_once dirname(__FILE__) . "/ThirdParty/ThirdParty.php";
	

	include_once dirname(__FILE__) . "/FirstParser/FirstParser.php";
	include_once dirname(__FILE__) . "/Executable/Executable.php";
	include_once dirname(__FILE__) . "/Core/Core.php";
	include_once dirname(__FILE__) . "/CoreTest/CoreTest.php";

	class CliffyC_Config extends Solution_Config
	{
		public function __construct($sAction)
		{
			parent::__construct($sAction);
			
			$this->m_pProjectArray[] = new Engine_Config($sAction);
			//$this->m_pProjectArray[] = new EngineJob_Config($sAction);
			$this->m_pProjectArray[] = new ThirdParty_Config($sAction);

			$this->m_pProjectArray[] = new FirstParser_Config($sAction);
			$this->m_pProjectArray[] = new Executable_Config($sAction);
			
			//if ($sAction == ACTION_WINDOWS_VS2008 || $sAction == ACTION_OSX_GMAKE || $sAction == ACTION_LINUX_GMAKE)
			{
				$this->m_pProjectArray[] = new Core_Config($sAction);
				$this->m_pProjectArray[] = new CoreTest_Config($sAction);
			}
		}

		public function GetName() { return "CliffyPDA"; }
	}

	ProjectGen(new CliffyC_Config(ProjectGen_GetAction()));
?>
