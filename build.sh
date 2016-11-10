mkdir -p ios_build
cmake . -Bios_build -GXcode -DUSER_BUILD_IOS=true
cd ios_build
xcodebuild -project clibraries.xcodeproj -target ALL_BUILD -configuration Release
cd ..
