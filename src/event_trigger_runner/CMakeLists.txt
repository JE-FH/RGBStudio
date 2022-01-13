set(HEADER_LIST 
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/event_trigger_runner/Event.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/event_trigger_runner/EventManager.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/event_trigger_runner/EventQueue.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/event_trigger_runner/EventTriggerController.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/event_trigger_runner/IEffectFactory.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/event_trigger_runner/IEventSource.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/event_trigger_runner/KeyEvent.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/event_trigger_runner/Trigger.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/event_trigger_runner/TriggerObserver.hpp"
	"${UniversalRGBDeviceController_SOURCE_DIR}/include/event_trigger_runner/TriggerObserverDispatcher.hpp"
)

add_library(event_trigger_runner STATIC 
	"EventManager.cpp"
	"EventQueue.cpp"
	"EventTriggerController.cpp"
	"KeyEvent.cpp"
	"TriggerObserver.cpp"
	"TriggerObserverDispatcher.cpp" 
	${HEADER_LIST}
)



target_include_directories(event_trigger_runner PUBLIC "${UniversalRGBDeviceController_SOURCE_DIR}/include")

target_link_libraries(event_trigger_runner PUBLIC device_adapter_loader)
target_link_libraries(event_trigger_runner PUBLIC effect_manager)

target_compile_features(event_trigger_runner PUBLIC cxx_std_20)


source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)
