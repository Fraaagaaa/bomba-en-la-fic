import {combineReducers} from 'redux';
import * as actionTypes from './actionTypes';

const initialState = {
    movies: null,
    movie: null,
    session: null,
    billboardDate: new Date().toISOString().split('T')[0]
};

const movies = (state = initialState.movies, action) => {
    switch (action.type) {
        case actionTypes.FIND_MOVIES_COMPLETED:
            return action.movies;

        case actionTypes.CLEAR_MOVIE_SEARCH:
            return initialState.movies;

        case actionTypes.CLEAR_BILLBOARD:
            return null;

        case actionTypes.GET_BILLBOARD_COMPLETED:
            return action.payload;

        default:
            return state;
    }
}

const movie = (state = initialState.movie, action) => {
    switch (action.type) {
        case actionTypes.GET_MOVIE_DETAILS_COMPLETED:
            return action.movie;
        case actionTypes.CLEAR_MOVIE_DETAILS:
            return initialState.movie;
        default:
            return state;
    }
}

const session = (state = initialState.session, action) => {
    switch (action.type) {
        case actionTypes.GET_SESSION_DETAILS_COMPLETED:
            return action.session;
        case actionTypes.CLEAR_SESSION_DETAILS: // Añadido
            return initialState.session;
        default:
            return state;
    }
}

const billboardDate = (state = initialState.billboardDate, action) => {
    switch (action.type) {
        case actionTypes.CLEAR_BILLBOARD:
            return action.date; // Actualizamos la fecha cuando se limpia la cartelera
        default:
            return state;
    }
}

const reducer = combineReducers({
    movies,
    movie,
    session,
    billboardDate
});

export default reducer;