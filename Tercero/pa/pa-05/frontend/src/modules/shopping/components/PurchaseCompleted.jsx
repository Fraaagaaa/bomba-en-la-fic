import { useSelector } from 'react-redux';
import { FormattedMessage } from 'react-intl';
import { Card } from 'react-bootstrap';
import app from '../../app';

const PurchaseCompleted = () => {
    const purchaseId = useSelector(app.selectors.getLastPurchaseId);

    if (!purchaseId) {
        return null;
    }

    return (
        <Card className="bg-light border-dark mt-3 mb-5">
            <Card.Header as="h5">
                <FormattedMessage id="project.shopping.PurchaseCompleted.title" />
            </Card.Header>
            <Card.Body>
                <div className="alert alert-success">
                    <FormattedMessage id="project.shopping.PurchaseCompleted.success" />
                    <strong id="purchase-id">{purchaseId}</strong>
                </div>
            </Card.Body>
        </Card>
    );
};

export default PurchaseCompleted;

