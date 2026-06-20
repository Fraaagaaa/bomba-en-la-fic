import {combineReducers} from 'redux';
import * as actionTypes from './actionTypes';

const initialState = {
    lastPurchase: null,
    purchaseSearch: null,
    lastDelivery: null
};

const lastDelivery = (state = initialState.lastDelivery, action) => {
    switch (action.type) {
        case actionTypes.DELIVER_TICKETS_COMPLETED:
            return action.deliveryDetails;
        default:
            return state;
    }
}

const lastPurchase = (state = initialState.lastPurchase, action) => {
    switch (action.type) {
        case actionTypes.PURCHASE_COMPLETED:
            return action.purchase;
        default:
            return state;
    }
}

const purchaseSearch = (state = initialState.purchaseSearch, action) => {
    switch (action.type) {
        case actionTypes.FIND_PURCHASES_COMPLETED:
            return action.purchaseSearch;
        case actionTypes.CLEAR_PURCHASE_SEARCH:
            return initialState.purchaseSearch;
        default:
            return state;
    }
}

const reducer = combineReducers({
    lastPurchase,
    purchaseSearch,
    lastDelivery
});

export default reducer;