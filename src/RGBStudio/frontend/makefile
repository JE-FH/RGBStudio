all: ../build/css/editor.css ../build/script/editor.m.js ../build/script/editor.m.js.map

#This is a last resort since node is extremely slow at starting up (3 seconds or so) delaying the entire build process every time you need to 
#recompile RGBStudio which end up being extremly annoying to deal with, therefore we have a make file that checks if rollup should even 
#be run, and then runs it, this is stupid, very stupid and this is a bad solution but who cares
../build/script/editor.m.js ../build/script/editor.m.js.map: ts/editor.m.ts \
ts/GraphEditor/GraphEditor.ts \
ts/GraphEditor/GraphNode.ts \
ts/GraphEditor/GraphNodeAttribute.ts \
ts/GraphEditor/NumberAttribute.ts \
ts/GraphEditor/ColorAttribute.ts \
ts/GraphEditor/SourceAttribute.ts \
ts/GraphEditor/TargetAttribute.ts \
ts/SVGCompositor/behavior/AutoSizer.ts \
ts/SVGCompositor/behavior/Dragifier.ts \
ts/SVGCompositor/CSEvent.ts \
ts/SVGCompositor/Line.ts \
ts/SVGCompositor/StyleHelper.ts \
ts/SVGCompositor/SVGCompositor.ts \
ts/SVGCompositor/SVGScratchArea.ts \
ts/SVGCompositor/trait/Circular.ts \
ts/SVGCompositor/trait/Clickable.ts \
ts/SVGCompositor/trait/Rectangular.ts \
ts/SVGCompositor/trait/Resizing.ts \
ts/SVGCompositor/Widget.ts \
ts/SVGCompositor/WidgetAtom.ts \
ts/SVGCompositor/WidgetConstructor.ts \
ts/SVGCompositor/WidgetContainer.ts \
ts/SVGCompositor/widgets/Circle.ts \
ts/SVGCompositor/widgets/ColorInputWidget.ts \
ts/SVGCompositor/widgets/FitContentContainer.ts \
ts/SVGCompositor/widgets/FlexBox.ts \
ts/SVGCompositor/widgets/LineEnd.ts \
ts/SVGCompositor/widgets/PaddedContainer.ts \
ts/SVGCompositor/widgets/StackPanel.ts \
ts/SVGCompositor/widgets/TextInputWidget.ts \
ts/SVGCompositor/widgets/TextWidget.ts \
ts/util.ts \
tsconfig.json \
rollup.config.js
	npx rollup -c rollup.config.js

../build/css/editor.css: less/editor.less
	npx less less/editor.less ../build/css/editor.css
