#This is a last resort since node is extremely slow at starting up (3 seconds or so) delaying the entire build process every time you need to 
#recompile RGBStudio which end up being extremly annoying to deal with, therefore we have a make file that checks if rollup should even 
#be run, and then runs it, this is stupid, very stupid and this is a bad solution but who cares
../build/script/editor.m.js ../build/script/editor.m.js.map: ts/editor.m.ts \
ts/GraphEditor/ConnectorType.ts \
ts/GraphEditor/GraphConnection.ts \
ts/GraphEditor/GraphConnector.ts \
ts/GraphEditor/GraphModel.ts \
ts/GraphEditor/GraphNode.ts \
ts/GraphEditor/GraphNodeAttribute.ts \
ts/GraphEditor/GraphSourceConnector.ts \
ts/GraphEditor/GraphTargetConnector.ts \
ts/GraphEditor/NumberAttribute.ts \
ts/GraphEditor/TriggerConnector.ts \
ts/GraphEditor/TriggerNode.ts \
ts/GraphEditor/ActionConnector.ts \
ts/GraphEditor/ActionNode.ts \
ts/SVGCompositor/Dragifier.ts \
ts/SVGCompositor/Event.ts \
ts/SVGCompositor/Line.ts \
ts/SVGCompositor/LineEnd.ts \
ts/SVGCompositor/Rectangle.ts \
ts/SVGCompositor/StyleHelper.ts \
ts/SVGCompositor/SVGCompositor.ts \
ts/SVGCompositor/Widget.ts \
ts/SVGCompositor/WidgetAtom.ts \
ts/SVGCompositor/WidgetContainer.ts \
tsconfig.json \
rollup.config.js
	npx rollup -c rollup.config.js