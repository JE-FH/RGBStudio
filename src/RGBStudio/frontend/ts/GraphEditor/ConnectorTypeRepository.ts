import { ConnectorType } from "./ConnectorType";

export default abstract class ConnectorTypeRepository {
    private static _registered_connectors: Map<string, ConnectorType> = new Map();

    public static register_connector_type(registered_name: string, connector_type: ConnectorType) {
        if (ConnectorTypeRepository._registered_connectors.has(registered_name)) {
            throw new Error("Tried to register connector with same name twice");
        }

        ConnectorTypeRepository._registered_connectors.set(registered_name, connector_type);
    }

    public static get_connector(registered_name: string): ConnectorType {
        let rv = ConnectorTypeRepository._registered_connectors.get(registered_name);
        if (rv == null) {
            throw new Error("Connector is not registered");
        }
        return rv;
    }
}