import {useEffect} from 'react';
import {useSelector, useDispatch} from 'react-redux';
import {useParams} from 'react-router';
import {FormattedMessage} from 'react-intl';

import * as actions from '../actions';
import * as selectors from '../selectors';
import {BackLink} from '../../common';

const MovieDetails = () => {
    const dispatch = useDispatch();
    const {id} = useParams();
    const movie = useSelector(selectors.getMovie);

    useEffect(() => {
        const movieId = Number(id);

        if (!isNaN(movieId)) {
            dispatch(actions.findMovieDetails(movieId));
        }

        return () => dispatch(actions.clearMovieDetails());

    }, [id, dispatch]);

    if (!movie) {
        return null;
    }

    return (
        <div>
            <div className="card text-center mt-3 mb-4">
                <div className="card-body">
                    <h5 className="card-title mb-3">
                        <strong><FormattedMessage id="project.global.fields.title"/>:</strong> {movie.title}
                    </h5>

                    <p className="card-text text-justify mb-3">
                        <strong><FormattedMessage id="project.global.fields.summary"/>:</strong> {movie.summary}
                    </p>

                    <h6 className="card-subtitle text-muted">
                        <strong><FormattedMessage id="project.global.fields.runtime"/>:</strong> {movie.duration} <FormattedMessage id="project.global.fields.minutes"/>
                    </h6>
                    <BackLink/>
                </div>
            </div>
        </div>
    );
}

export default MovieDetails;