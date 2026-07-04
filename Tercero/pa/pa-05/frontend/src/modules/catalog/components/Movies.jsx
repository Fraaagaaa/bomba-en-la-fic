import {FormattedMessage, FormattedTime} from 'react-intl';
import Table from 'react-bootstrap/Table';
import {Link} from 'react-router';
import PropTypes from 'prop-types';

const Movies = ({movies}) => {

    if (!movies || movies.length === 0) {
        return null;
    }

    const now = new Date();

    const upcomingMovies = movies.reduce((result, item) => {
        const validSessions = item.sessions.filter(session => {
            return new Date(session.sessionStartTime) > now;
        });

        if (validSessions.length > 0) {
            result.push({
                ...item,
                sessions: validSessions
            });
        }

        return result;
    }, []);

    return (
        <Table striped hover>
            <thead>
            <tr>
                <th>
                    <FormattedMessage id='project.global.fields.title'/>
                </th>
                <th>
                    <FormattedMessage id='project.catalog.fields.sessions'/>
                </th>
            </tr>
            </thead>

            <tbody>
            {upcomingMovies.map(item =>
                <tr key={item.movie.id}>
                    <td>
                        <Link className="movie-link" to={`/catalog/movie-details/${item.movie.id}`}>
                            <strong>{item.movie.title}</strong>
                        </Link>
                    </td>

                    <td>
                        {item.sessions.map((session, index) => (
                            <span key={session.id}>
                                <Link className="session-link" to={`/catalog/session-details/${session.id}`}>
                                    <FormattedTime value={new Date(session.sessionStartTime)}/>
                                </Link>
                                {index < item.sessions.length - 1 && ' | '}
                            </span>
                        ))}
                    </td>
                </tr>
            )}
            </tbody>
        </Table>
    );
};

Movies.propTypes = {
    movies: PropTypes.array
};

export default Movies;