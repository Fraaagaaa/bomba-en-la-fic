import { useEffect } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import Movies from './Movies';
import DateSelector from './DateSelector';
import * as actions from '../actions';
import * as selectors from '../selectors';
import backend from '../../../backend';
import {FormattedMessage} from "react-intl";

const Billboard = () => {
    const dispatch = useDispatch();
    const movies = useSelector(selectors.getMovies);
    const billboardDate = useSelector(selectors.getBillboardDate);

    const handleBillboardDateChange = async (date) => {
        dispatch(actions.clearBillboard(date));
        const response = await backend.catalogService.getBillboard(date);

        if (response.ok) {
            dispatch(actions.getBillboardCompleted(response.payload));
        } else {
            dispatch(actions.getBillboardCompleted([]));
        }
    };

    useEffect(() => {
        if (!movies) {
            handleBillboardDateChange(billboardDate);
        }
    }, []);

    return (
        <div>
            <h2 className="mb-4 text-center mt-4"><FormattedMessage id="project.global.fields.billboard"/></h2>

            <div className="d-flex justify-content-center mb-4">
                <DateSelector
                    id="billboardDate"
                    className="mb-2 w-auto"
                    value={billboardDate}
                    onChange={date => handleBillboardDateChange(date)}
                />
            </div>

            {!movies ? (
                <div className="text-center">
                    <div className="spinner-border text-primary" role="status">
                        <span className="visually-hidden"></span>
                    </div>
                </div>
            ) : (
                <Movies movies={movies}/>
            )}
        </div>
    );
}

export default Billboard;