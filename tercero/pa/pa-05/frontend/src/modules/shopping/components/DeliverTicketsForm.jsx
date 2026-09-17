import { useState } from 'react';
import { useDispatch } from 'react-redux';
import { Form, Button, Card, Col } from 'react-bootstrap';
import * as actions from '../actions';
import backend from '../../../backend';
import { FormattedMessage, useIntl } from 'react-intl';
import { Errors, Success } from '../../common';

const DeliverTicketsForm = () => {
    const dispatch = useDispatch();
    const intl = useIntl();

    const [purchaseId, setPurchaseId] = useState('');
    const [creditCard, setCreditCard] = useState('');

    const [backendErrors, setBackendErrors] = useState(null);
    const [successMessage, setSuccessMessage] = useState(null);
    const [formValidated, setFormValidated] = useState(false);

    let form;

    const handleSubmit = async (event) => {
        event.preventDefault();

        if (form.checkValidity()) {
            const response = await backend.shoppingService.deliverTickets(purchaseId, creditCard);

            if (response.ok) {
                dispatch(actions.deliverTicketsCompleted(response.payload));

                setSuccessMessage(intl.formatMessage({ id: 'project.shopping.DeliverTicketsForm.success' }));
                setBackendErrors(null);

                setPurchaseId('');
                setCreditCard('');
                setFormValidated(false);
            } else {
                console.log("Error del backend:", response);
                setBackendErrors(response.payload);
                setSuccessMessage(null);
            }
        } else {
            setBackendErrors(null);
            setSuccessMessage(null);
            setFormValidated(true);
        }
    };

    return (
        <div>
            <Errors errors={backendErrors} onClose={() => setBackendErrors(null)} />
            <Success message={successMessage} onClose={() => setSuccessMessage(null)} />

            <Card className="mt-3 mb-5">
                <Card.Header as="h5">
                    <FormattedMessage id="project.shopping.DeliverTicketsForm.title" />
                </Card.Header>
                <Card.Body>
                    <Form ref={node => form = node} noValidate validated={formValidated} onSubmit={handleSubmit}>

                        <Form.Group controlId="purchaseId" className="mb-3">
                            <Form.Label>
                                <FormattedMessage id="project.shopping.DeliverTicketsForm.purchaseId" />
                            </Form.Label>
                            <Col>
                                <Form.Control
                                    type="number"
                                    value={purchaseId}
                                    onChange={e => setPurchaseId(e.target.value)}
                                    autoFocus
                                    required
                                />
                                <Form.Control.Feedback type="invalid">
                                    <FormattedMessage id="project.shopping.DeliverTicketsForm.purchaseIdRequired" />
                                </Form.Control.Feedback>
                            </Col>
                        </Form.Group>

                        <Form.Group controlId="creditCard" className="mb-3">
                            <Form.Label>
                                <FormattedMessage id="project.shopping.DeliverTicketsForm.creditCard" />
                            </Form.Label>
                            <Col>
                                <Form.Control
                                    type="text"
                                    value={creditCard}
                                    onChange={e => setCreditCard(e.target.value)}
                                    required
                                />
                                <Form.Control.Feedback type="invalid">
                                    <FormattedMessage id="project.shopping.DeliverTicketsForm.creditCardRequired" />
                                </Form.Control.Feedback>
                            </Col>
                        </Form.Group>

                        <Form.Group>
                            <Col>
                                <Button type="submit" variant="primary">
                                    <FormattedMessage id="project.shopping.DeliverTicketsForm.deliver" />
                                </Button>
                            </Col>
                        </Form.Group>

                    </Form>
                </Card.Body>
            </Card>
        </div>
    );
};

export default DeliverTicketsForm;