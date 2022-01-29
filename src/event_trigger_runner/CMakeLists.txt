set(HEADER_LIST 
	"${RGBStudio_SOURCE_DIR}/include/event_trigger_runner/Event.hpp"
	"${RGBStudio_SOURCE_DIR}/include/event_trigger_runner/EventManager.hpp"
	"${RGBStudio_SOURCE_DIR}/include/event_trigger_runner/EventQueue.hpp"
	"${RGBStudio_SOURCE_DIR}/include/event_trigger_runner/EventTriggerController.hpp"
	"${RGBStudio_SOURCE_DIR}/include/event_trigger_runner/IEffectFactory.hpp"
	"${RGBStudio_SOURCE_DIR}/include/event_trigger_runner/IEventSource.hpp"
	"${RGBStudio_SOURCE_DIR}/include/event_trigger_runner/KeyEvent.hpp"
	"${RGBStudio_SOURCE_DIR}/include/event_trigger_runner/Trigger.hpp"
	"${RGBStudio_SOURCE_DIR}/include/event_trigger_runner/TriggerObserver.hpp"
	"${RGBStudio_SOURCE_DIR}/include/event_trigger_runner/TriggerObserverDispatcher.hpp"
	"${RGBStudio_SOURCE_DIR}/include/event_trigger_runner/default_triggers/KeyTrigger.hpp"
	"${RGBStudio_SOURCE_DIR}/include/event_trigger_runner/default_triggers/KeyTriggerFactory.hpp"
)

add_library(event_trigger_runner STATIC 
	"EventManager.cpp"
	"EventQueue.cpp"
	"EventTriggerController.cpp"
	"KeyEvent.cpp"
	"TriggerObserver.cpp"
	"TriggerObserverDispatcher.cpp" 
	"default_triggers/KeyTrigger.cpp" 
	"default_triggers/KeyTriggerFactory.cpp" 
	${HEADER_LIST}
)



target_include_directories(event_trigger_runner PUBLIC "${RGBStudio_SOURCE_DIR}/include")

target_link_libraries(event_trigger_runner PUBLIC device_adapter_loader)
target_link_libraries(event_trigger_runner PUBLIC effect_manager)
target_link_libraries(event_trigger_runner PUBLIC dynamic_config)

target_compile_features(event_trigger_runner PUBLIC cxx_std_20)


source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)
