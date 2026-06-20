import {useEffect} from 'react';
import {useSelector, useDispatch} from 'react-redux';
import {FormattedMessage, FormattedDate, FormattedTime, FormattedNumber} from 'react-intl';
import Table from 'react-bootstrap/Table';

import * as actions from '../actions';
import {getPurchaseSearch} from '../selectors';
import backend from '../../../backend';
import {Pager} from '../../common';

const PurchaseHistory = () => {
    const dispatch = useDispatch();
    const purchaseSearch = useSelector(getPurchaseSearch);

    useEffect(() => {
        const fetchPurchases = async () => {
            dispatch(actions.clearPurchaseSearch());
            const response = await backend.shoppingService.findPurchases(0);

            if (response.ok) {
                dispatch(actions.findPurchasesCompleted({
                    criteria: { page: 0 },
                    result: response.payload
                }));
            } else {
                // Si la respuesta no es OK (ej. 403), despachamos un resultado vacío para quitar el spinner
                dispatch(actions.findPurchasesCompleted({
                    criteria: { page: 0 },
                    result: { items: [], existMoreItems: false }
                }));
            }
        };
        fetchPurchases();

        return () => dispatch(actions.clearPurchaseSearch());
    }, [dispatch]);

    const fetchPage = async (page) => {
        const response = await backend.shoppingService.findPurchases(page);
        if (response.ok) {
            dispatch(actions.findPurchasesCompleted({
                criteria: { page },
                result: response.payload
            }));
        }
    };

    if (!purchaseSearch) {
        return (
            <div className="text-center mt-4">
                <div className="spinner-border text-primary" role="status">
                    <span className="visually-hidden">Cargando...</span>
                </div>
            </div>
        );
    }

    if (purchaseSearch.result.items.length === 0) {
        return (
            <div className="alert alert-info mt-4" role="alert">
                <FormattedMessage id='project.shopping.PurchaseHistory.noPurchases'/>
            </div>
        );
    }

    return (
        <div className="mt-4">
            <h2 className="mb-4 text-center">
                <FormattedMessage id="project.shopping.PurchaseHistory.title"/>
            </h2>
            <Table striped hover>
                <thead>
                <tr>
                    <th><FormattedMessage id='project.shopping.PurchaseHistory.purchaseDate'/></th>
                    <th><FormattedMessage id='project.shopping.PurchaseHistory.purchaseId'/></th>
                    <th><FormattedMessage id='project.shopping.PurchaseHistory.movie'/></th>
                    <th><FormattedMessage id='project.shopping.PurchaseHistory.tickets'/></th>
                    <th><FormattedMessage id='project.shopping.PurchaseHistory.price'/></th>
                    <th><FormattedMessage id='project.shopping.PurchaseHistory.sessionDate'/></th>
                    <th><FormattedMessage id='project.shopping.PurchaseHistory.delivered'/></th>
                </tr>
                </thead>
                <tbody>
                {purchaseSearch.result.items.map(purchase => (
                    <tr key={purchase.id}>
                        <td>
                            <FormattedDate value={new Date(purchase.purchaseDate)}/> - <FormattedTime value={new Date(purchase.purchaseDate)}/>
                        </td>
                        <td>{purchase.id}</td>
                        <td>{purchase.movieTitle}</td>
                        <td>{purchase.ticketAmmount}</td>
                        <td><FormattedNumber value={purchase.totalPrice} style="currency" currency="EUR"/></td>
                        <td>
                            <FormattedDate value={new Date(purchase.sessionDate)}/> - <FormattedTime value={new Date(purchase.sessionDate)}/>
                        </td>
                        <td>
                            <FormattedMessage id={purchase.recogidas ? 'project.shopping.PurchaseHistory.yes' : 'project.shopping.PurchaseHistory.no'}/>
                        </td>
                    </tr>
                ))}
                </tbody>
            </Table>

            <Pager
                back={{
                    enabled: purchaseSearch.criteria.page >= 1,
                    onClick: () => fetchPage(purchaseSearch.criteria.page - 1)
                }}
                next={{
                    enabled: purchaseSearch.result.existMoreItems,
                    onClick: () => fetchPage(purchaseSearch.criteria.page + 1)
                }}
            />
        </div>
    );
};

export default PurchaseHistory;