const getModuleState = state => state.app;

export const getError = state => getModuleState(state).error;

export const getLastPurchaseId = state => getModuleState(state).lastPurchaseId;

