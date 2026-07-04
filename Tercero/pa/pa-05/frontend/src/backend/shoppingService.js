import { appFetch } from './appFetch';

export const buy = (sessionId, quantity, creditCard) =>
    appFetch('POST', '/shopping/buy', { sessionId, quantity, creditCard });

export const findPurchases = (page) =>
    appFetch('GET', `/shopping/purchases?page=${page}`);

export const deliverTickets = (purchaseId, creditCard) =>
    appFetch('POST', `/shopping/purchases/${purchaseId}/deliver`, { creditCard });
