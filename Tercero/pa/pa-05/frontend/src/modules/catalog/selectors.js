const getModuleState = state => state.catalog;

export const getMovies = state => getModuleState(state).movies;
export const getMovie = state => getModuleState(state).movie;
export const getBillboardDate = state => getModuleState(state).billboardDate;
export const getSession = state => getModuleState(state).session;