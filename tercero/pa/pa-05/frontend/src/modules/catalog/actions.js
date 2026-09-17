import * as actionTypes from './actionTypes';
import backend from '../../backend';

export const findMoviesCompleted = movies => ({
    type: actionTypes.FIND_MOVIES_COMPLETED,
    movies
});

export const clearMovieSearch = () => ({
    type: actionTypes.CLEAR_MOVIE_SEARCH
});

export const getMovieDetailsCompleted = movie => ({
    type: actionTypes.GET_MOVIE_DETAILS_COMPLETED,
    movie
});

export const clearMovieDetails = () => ({
    type: actionTypes.CLEAR_MOVIE_DETAILS
});

export const getSessionDetailsCompleted = session => ({
    type: actionTypes.GET_SESSION_DETAILS_COMPLETED,
    session
});

export const findMovieDetails = id => async dispatch => {
    dispatch(clearMovieDetails());

    const response = await backend.catalogService.getMovieDetails(id);
    if (response.ok) {
        dispatch(getMovieDetailsCompleted(response.payload));
    }
};

export const clearBillboard = (date) => ({
    type: actionTypes.CLEAR_BILLBOARD,
    date
});

export const getBillboardCompleted = (payload) => ({
    type: actionTypes.GET_BILLBOARD_COMPLETED,
    payload
});

export const clearSessionDetails = () => ({
    type: actionTypes.CLEAR_SESSION_DETAILS
});

export const findSessionDetails = (id, onErrors) => async dispatch => {
    dispatch(clearSessionDetails());
    const response = await backend.catalogService.getSessionDetails(id);
    if (response.ok) {
        dispatch(getSessionDetailsCompleted(response.payload));
    } else if (onErrors) {
        onErrors(response.payload);
    }
};
