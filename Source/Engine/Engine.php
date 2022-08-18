<?php
	class Engine_Config extends Project_Config
	{
		
		public function __construct($sAction)
		{
			parent::__construct($sAction);
			
			$sRegex = "/\.h|\.c/";
			if ($this->m_sAction == ACTION_IOS_XCODE || $this->m_sAction == ACTION_WINDOWS_VS2008)
				$sRegex = "/\.h|\.c|\.m/";
			
			$this->m_xFileArray = ProjectGen_ParseDirectory(dirname(__FILE__), $sRegex);
		}

		public function GetName() { return "Engine"; }
		public function GetKind() { return KIND_STATIC_LIBRARY; }
		//public function GetLocation() { return "..\\" . $this->GetName() . "\\" . $this->m_sAction . "\\"; }
		public function GetBaseDirectory() { return dirname(__FILE__); }

		public function GetBuildOptionArray($sConfiguration, $sArchitecture)
		{
			$sArray = array();

			if ($this->m_sAction == ACTION_OSX_GMAKE || $this->m_sAction == ACTION_EMSCRIPTEN_GMAKE)
			{
				$sArray = array_merge($sArray, array(
					"-std=c89",
					"-Werror",
					"-Wall",
					"-Wextra",
					"-Wmissing-prototypes",
					"-Wstrict-prototypes",
					"-Wold-style-definition",
					"-pedantic",
						"-Wno-comment",
						"-Wno-newline-eof",
						"-Wno-long-long",
						"-Wno-overlength-strings",
						"-Wno-unused-parameter",
						"-Wno-empty-translation-unit",

						"-Wno-c99-extensions"
				));
			}

			return $sArray;
		}

		public function GetIncludeDirectoryArray($sConfiguration, $sArchitecture)
		{
			$sArray = array(
				
				//"../EngineJob",
				"../Engine", // hax so workers can include nbType.h
				"../ThirdParty",
				);

			if ($this->m_sAction == ACTION_WINDOWS_VS2008)
			{
				$sArray[] = "../../Library/Windows/GLEW/include";
				$sArray[] = "../../Library/Windows/GLFW/include";
				$sArray[] = "../../Library/Windows/dsound";
				//$sArray[] = "../../../Library/Windows/libcurl/include";
			}

			if ($this->m_sAction == ACTION_OSX_GMAKE)
			{
				//$sArray[] = "/opt/local/include/"; // no longer works??
				$sArray[] = "/usr/local/include/"; // replace with this???
			}
			
			if ($this->m_sAction == ACTION_IOS_XCODE)
			{
				$sArray[] = "../../Library/iOs/libcurl/include";
				/*$sArray[] = "../../Library/iOs/Firebase";
				$sArray[] = "../../Library/iOs/Firebase/Analytics";
				$sArray[] = "../../Library/iOs/Firebase/AdMob";*/
			}
			
			if ($this->m_sAction == ACTION_ANDROID_GRADLE)
			{
				$sArray[] = "../../Library/Android/libcurl/include";
			}



			
			return $sArray;
		}

		public function GetDependancyArray()
		{
			$sArray = array(
				"ThirdParty",
				//"EngineJob",
			);

			if ($this->m_sAction == ACTION_WINDOWS_VS2008)
			{
				$sArray[] = "..\..\..\..\Library\Windows\GLEW\lib\glew32.lib";
				$sArray[] = "..\..\..\..\Library\Windows\GLFW\lib-msvc90\GLFW.lib";
				$sArray[] = "..\..\..\..\Library\Windows\dsound\dsound.lib";
				$sArray[] = "opengl32.lib";
				$sArray[] = "glu32.lib";
				$sArray[] = "Ws2_32.lib";
				$sArray[] = "winhttp.lib";
				//$sArray[] = "..\..\..\Library\Windows\libcurl\lib\dll-release\libcurl.lib";
			}

			if ($this->m_sAction == ACTION_OSX_GMAKE)
			{
				$sArray = array_merge($sArray, array(
					"/usr/local/lib/libGLEW.dylib",
					"/usr/local/lib/libglfw.3.dylib",
					"/usr/lib/libcurl.dylib",
				));
			}
			
			if ($this->m_sAction == ACTION_IOS_XCODE)
			{
				$sArray[] = "../../Library/iOs/libcurl/lib/libcurl.a"; // remove one day
				$sArray[] = "/usr/lib/libz.tbd"; // remove with libcurl
				$sArray[] = "/System/Library/Frameworks/Security.framework";
				
				// ads!
				//$sArray[] = "../../Library/iOs/Firebase/Analytics/FirebaseAnalytics.framework";
				//$sArray[] = "../../Library/iOs/Firebase/Analytics/FirebaseCore.framework";
				//$sArray[] = "../../Library/iOs/Firebase/Analytics/FirebaseInstanceID.framework";
				//$sArray[] = "../../Library/iOs/Firebase/Analytics/GoogleToolboxForMac.framework";
				//$sArray[] = "../../Library/iOs/Firebase/AdMob/GoogleMobileAds.framework";
				$sArray[] = "/System/Library/Frameworks/CoreMotion.framework";
				$sArray[] = "/System/Library/Frameworks/StoreKit.framework";
				$sArray[] = "/System/Library/Frameworks/CoreTelephony.framework";
				$sArray[] = "/System/Library/Frameworks/AVFoundation.framework";
				$sArray[] = "/System/Library/Frameworks/MessageUI.framework";
				$sArray[] = "/System/Library/Frameworks/CoreServices.framework";
				$sArray[] = "/System/Library/Frameworks/SystemConfiguration.framework";
				$sArray[] = "/usr/lib/libsqlite3.tbd";
			}

			if ($this->m_sAction == ACTION_ANDROID_GRADLE)
			{
				$sArray[] = "../../../../Library/Android/libcurl/lib/\${ANDROID_ABI}/libcurl.a"; // remove one day?
			}

			if ($this->m_sAction == ACTION_LINUX_GMAKE)
			{
				$sArray = array_merge($sArray, array(
					"-lGL",
					"-lGLEW",
					"-lGL",
					"-ldl",
					"-lpthread",
					"-lcurl",
					"-lglfw",
				));
			}

			if ($this->m_sAction == ACTION_CMAKE)
			{
				$sArray = array_merge($sArray, array(
					"GL",
					"GLEW",
					"dl",
					"pthread",
					"curl",
					"glfw",
				));
			}
			
			return $sArray;
		}
	}
?>
