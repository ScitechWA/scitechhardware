// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using System.IO;
using System;

namespace UnrealBuildTool.Rules
{
    public class ScitechHardware : ModuleRules
    {
        private string ModulePath
        {
            get { return ModuleDirectory; }
        }

        private string ThirdPartyPath
        {
            get { return Path.GetFullPath(Path.Combine(ModulePath, "../ThirdParty/")); }
        }

        private string BinariesPath
        {
            get { return Path.GetFullPath(Path.Combine(ModulePath, "../../Binaries/")); }
        }

        public ScitechHardware(ReadOnlyTargetRules Target) : base(Target)
        {
            //PrivateIncludePaths.Add("ScitechHardware/Private");
            //PublicIncludePaths.Add("ScitechHardware/Public");

            PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Slate", "SlateCore", "SerialStaticLib" });
            PrivateDependencyModuleNames.AddRange(new string[] { "Core" });

            // Since the PCL module needs this, we also have to use these flags here
            bUseRTTI = true;
            bEnableExceptions = true;
            //Definitions.Add("BOOST_NO_RTTI");
            //bEnableUndefinedIdentifierWarnings = false;
        }
    }
}
