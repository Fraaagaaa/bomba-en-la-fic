import * as actionTypes from './actionTypes';

export const purchaseCompleted = purchase => ({
    type: actionTypes.PURCHASE_COMPLETED,
    purchase
});

export const findPurchasesCompleted = purchaseSearch => ({
    type: actionTypes.FIND_PURCHASES_COMPLETED,
    purchaseSearch
});

export const clearPurchaseSearch = () => ({
    type: actionTypes.CLEAR_PURCHASE_SEARCH
});

export const deliverTicketsCompleted = (deliveryDetails) => ({
    type: actionTypes.DELIVER_TICKETS_COMPLETED,
    deliveryDetails
});