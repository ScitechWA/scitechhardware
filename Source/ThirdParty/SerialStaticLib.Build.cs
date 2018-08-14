// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using System.IO;
using System;

namespace UnrealBuildTool.Rules
{
    public class SerialStaticLib : ModuleRules
    {
        private string ModulePath
        {
            get { return ModuleDirectory; }
        }

        private string BinariesPath
        {
            get { return Path.GetFullPath(Path.Combine(ModulePath, "../Binaries/")); }
        }

        public SerialStaticLib(ReadOnlyTargetRules Target) : base(Target)
        {
            // Tell Unreal that this Module only imports Third-Party-Assets
            Type = ModuleType.External;

            LoadSerialStaticLib(Target);
        }

        public bool LoadSerialStaticLib(ReadOnlyTargetRules Target)
        {
            bool isLibrarySupported = false;
            //bool bDebug = (Target.Configuration == UnrealTargetConfiguration.Debug && BuildConfiguration.bDebugBuildsActuallyUseDebugCRT);

            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                isLibrarySupported = true;

                //string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";

                // Explicitly name the used libraries
                //PublicAdditionalLibraries.Add(Path.Combine(ModulePath, "Boost/lib/libboost_chrono-vc141-mt-1_64.lib"));
                //Log.TraceInformation(Path.Combine(ModulePath, @"ofxCVFace\lib\ofxCvFace.lib"));

                PublicAdditionalLibraries.Add(Path.Combine(ModulePath, @"SerialStaticLib\lib\SerialComms.lib"));
            }

            if (isLibrarySupported)
            {
                PublicIncludePaths.Add(Path.Combine(ModulePath, "SerialStaticLib/include"));
                //PublicIncludePaths.Add(Path.Combine(ModulePath, "FLANN/include"));
                //PublicIncludePaths.Add(Path.Combine(ModulePath, "VTK/include/vtk-8.0"));

                // Not sure if needed
                //Definitions.Add("_CRT_SECURE_NO_WARNINGS=1");
                //Definitions.Add("BOOST_DISABLE_ABI_HEADERS=1");

                // Needed configurations in order to run Boost
                bUseRTTI = true;
                bEnableExceptions = true;
                //bEnableUndefinedIdentifierWarnings = false;
            }

            PublicDefinitions.Add(string.Format("WITH_SERIALSTATIC_BINDING={0}", isLibrarySupported ? 1 : 0));

            return isLibrarySupported;
        }
    }
}
