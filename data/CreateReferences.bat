cd Reference-oax
cd 31696c04-386a-4407-8f3e-c3f6e92d91ca
7z a -tzip 31696c04-386a-4407-8f3e-c3f6e92d91ca.oax apple_pc.mtl apple_pc.obj content.xml

cd ..
cd 31696c04-386a-4407-8f3e-c3f6e92d91cb
7z a -tzip 31696c04-386a-4407-8f3e-c3f6e92d91cb.oax TIE.mtl tie.obj content.xml

cd ..
cd 31696c04-386a-4407-8f3e-c3f6e92d91cc
7z a -tzip 31696c04-386a-4407-8f3e-c3f6e92d91cc.oax apple-ibook-2001.mtl apple-ibook-2001.obj content.xml

cd ..
cd 31696c04-386a-4407-8f3e-c3f6e92d91cd
7z a -tzip 31696c04-386a-4407-8f3e-c3f6e92d91cd.oax stardestroyer.mtl stardestroyer.obj content.xml

cd ..

move /Y 31696c04-386a-4407-8f3e-c3f6e92d91ca\31696c04-386a-4407-8f3e-c3f6e92d91ca.oax
move /Y 31696c04-386a-4407-8f3e-c3f6e92d91cb\31696c04-386a-4407-8f3e-c3f6e92d91cb.oax
move /Y 31696c04-386a-4407-8f3e-c3f6e92d91cc\31696c04-386a-4407-8f3e-c3f6e92d91cc.oax
move /Y 31696c04-386a-4407-8f3e-c3f6e92d91cd\31696c04-386a-4407-8f3e-c3f6e92d91cd.oax

cd ..
cd Reference-opx

copy /Y .\..\Reference-oax\31696c04-386a-4407-8f3e-c3f6e92d91ca.oax .\ExampleProject\assemblies
copy /Y .\..\Reference-oax\31696c04-386a-4407-8f3e-c3f6e92d91cb.oax .\ExampleProject\assemblies
copy /Y .\..\Reference-oax\31696c04-386a-4407-8f3e-c3f6e92d91cc.oax .\ExampleProject\assemblies
copy /Y .\..\Reference-oax\31696c04-386a-4407-8f3e-c3f6e92d91cd.oax .\ExampleProject\assemblies

cd ExampleProject 
7z a -tzip ExampleProject.opx content.xml assemblies\31696c04-386a-4407-8f3e-c3f6e92d91ca.oax assemblies\31696c04-386a-4407-8f3e-c3f6e92d91cb.oax assemblies\31696c04-386a-4407-8f3e-c3f6e92d91cc.oax assemblies\31696c04-386a-4407-8f3e-c3f6e92d91cd.oax 

cd ..
move /Y .\ExampleProject\ExampleProject.opx 