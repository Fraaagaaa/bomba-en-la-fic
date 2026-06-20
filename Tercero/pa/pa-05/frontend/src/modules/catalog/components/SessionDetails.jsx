import { useEffect, useState } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { useParams, Link } from 'react-router-dom';
import { FormattedMessage, FormattedDate, FormattedTime, FormattedNumber } from 'react-intl';

import * as selectors from '../selectors';
import * as actions from '../actions';
import { Errors, BackLink } from '../../common';
import BuyForm from '../../shopping/components/BuyForm';

const SessionDetails = () => {
    const dispatch = useDispatch();
    const { id } = useParams();
    const session = useSelector(selectors.getSession);
    const [backendErrors, setBackendErrors] = useState(null);

    useEffect(() => {
        const sessionId = Number(id);
        if (!isNaN(sessionId)) {
            dispatch(actions.findSessionDetails(sessionId, errors => setBackendErrors(errors)));
        }
        return () => dispatch(actions.clearSessionDetails());
    }, [id, dispatch]);

    if (backendErrors) {
        return (
            <div>
                <Errors errors={backendErrors} onClose={() => setBackendErrors(null)} />
                <BackLink />
            </div>
        );
    }

    if (!session) {
        return null;
    }

    return (
        <div>
            <div className="card mt-3 border-dark">
                <div className="card-body">
                    <h4 className="card-title mb-4">
                        <Link id="movie-title" to={`/catalog/movie-details/${session.movieId}`}>
                            {session.movieTitle}
                        </Link>
                    </h4>
                    <div className="card-text">
                        <p id="runtime">
                            <strong><FormattedMessage id="project.global.fields.runtime"/>:</strong> {session.movieRuntime} <FormattedMessage id="project.global.fields.minutes"/>
                        </p>
                        <p id="price">
                            <strong><FormattedMessage id="project.global.fields.price"/>:</strong> <FormattedNumber value={session.price} style="currency" currency="EUR"/>
                        </p>
                        <p id="date">
                            <strong><FormattedMessage id="project.global.fields.date"/>:</strong> <FormattedDate value={new Date(session.sessionStartTime)} />
                        </p>
                        <p id="time">
                            <strong><FormattedMessage id="project.global.fields.time"/>:</strong> <FormattedTime value={new Date(session.sessionStartTime)} />
                        </p>
                        <p id="room-name">
                            <strong><FormattedMessage id="project.catalog.fields.saloon"/>:</strong> {session.saloonName}
                        </p>
                        <p id="available-seats">
                            <strong><FormattedMessage id="project.catalog.fields.availableSeats"/>:</strong> {session.availableSeats}
                        </p>
                    </div>
                    {session.availableSeats > 0 && (
                        <div className="mt-4">
                            <BuyForm />
                        </div>
                    )}
                </div>
            </div>
            <div className="mt-3">
                <BackLink />
            </div>
        </div>
    );
};

export default SessionDetails;
