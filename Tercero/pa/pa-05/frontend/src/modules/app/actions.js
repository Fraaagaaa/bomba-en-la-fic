import * as actionTypes from './actionTypes';

export const error = error => ({
    type: actionTypes.ERROR,
    error
});

export const buyCompleted = (purchaseId) => ({
    type: actionTypes.BUY_COMPLETED,
    purchaseId
});