import { appFetch } from './appFetch';

export const getBillboard = (date) =>
    appFetch('GET', `/catalog/movies?date=${date}`);

export const getMovieDetails = (id) =>
    appFetch('GET', `/catalog/movies/${id}`);

export const getSessionDetails = (id) =>
    appFetch('GET', `/catalog/sessions/${id}`);
