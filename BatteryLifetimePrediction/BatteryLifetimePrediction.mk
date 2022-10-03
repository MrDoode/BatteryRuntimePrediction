##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=BatteryLifetimePrediction
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/janosch/Scripts/cpp/Erste_Versuche
ProjectPath            :=/home/janosch/Scripts/cpp/Erste_Versuche/BatteryLifetimePrediction
IntermediateDirectory  :=../build-$(ConfigurationName)/BatteryLifetimePrediction
OutDir                 :=../build-$(ConfigurationName)/BatteryLifetimePrediction
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=07/15/22
CodeLitePath           :=/home/janosch/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../build-$(ConfigurationName)/bin/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=../build-$(ConfigurationName)/BatteryLifetimePrediction/main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/BatteryLifetimePrediction/.d $(Objects) 
	@mkdir -p "../build-$(ConfigurationName)/BatteryLifetimePrediction"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "../build-$(ConfigurationName)/BatteryLifetimePrediction"
	@mkdir -p ""../build-$(ConfigurationName)/bin""

../build-$(ConfigurationName)/BatteryLifetimePrediction/.d:
	@mkdir -p "../build-$(ConfigurationName)/BatteryLifetimePrediction"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/BatteryLifetimePrediction/main.cpp$(ObjectSuffix): main.cpp ../build-$(ConfigurationName)/BatteryLifetimePrediction/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/janosch/Scripts/cpp/Erste_Versuche/BatteryLifetimePrediction/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/BatteryLifetimePrediction/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/BatteryLifetimePrediction/main.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/BatteryLifetimePrediction/main.cpp$(DependSuffix) -MM main.cpp

../build-$(ConfigurationName)/BatteryLifetimePrediction/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/BatteryLifetimePrediction/main.cpp$(PreprocessSuffix) main.cpp


-include ../build-$(ConfigurationName)/BatteryLifetimePrediction//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


