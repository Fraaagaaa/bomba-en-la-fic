import { useState } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { FormattedMessage, useIntl } from 'react-intl';
import { useParams, useNavigate } from 'react-router';
import { Errors, Success } from '../../common';
import backend from '../../../backend';
import users from '../../users';
import app from '../../app';
import * as catalogActions from '../../catalog/actions';
import { Card, Form, Col, Button } from 'react-bootstrap';

const BuyForm = () => {
    const { id: sessionId } = useParams();
    const intl = useIntl();
    const dispatch = useDispatch();
    const navigate = useNavigate();
    const user = useSelector(users.selectors.getUser);

    const [quantity, setQuantity] = useState(1);
    const [creditCard, setCreditCard] = useState('');
    const [backendErrors, setBackendErrors] = useState(null);
    const [successMessage, setSuccessMessage] = useState(null);
    const [formValidated, setFormValidated] = useState(false);

    let form;

    if (!user || user.role !== 'USER') {
        return null;
    }

    const handleSubmit = async (event) => {
        event.preventDefault();

        if (form.checkValidity()) {
            try {
                const response = await backend.shoppingService.buy(sessionId, quantity, creditCard);

                if (response && response.ok) {
                    dispatch(app.actions.buyCompleted(response.payload.id));
                    dispatch(catalogActions.findSessionDetails(Number(sessionId), (errors) => {
                        console.error("Error al actualizar sesión:", errors);
                    }));
                    navigate('/shopping/purchase-completed');
                } else if (response) {
                    setBackendErrors(response.payload);
                    setSuccessMessage(null);
                }
            } catch (error) {
                console.error("Error en la ejecución de la compra:", error);
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

            <Card className="bg-light border-dark mt-3 mb-5">
                <Card.Header as="h5">
                    <FormattedMessage id="project.shopping.buyform.title"/>
                </Card.Header>
                <Card.Body>
                    <Form ref={node => form = node}
                          validated={formValidated}
                          noValidate
                          onSubmit={handleSubmit}>

                        <Form.Group controlId="quantity" className="mb-3">
                            <Form.Label>
                                <FormattedMessage id="project.shopping.buyform.quantity"/>
                            </Form.Label>
                            <Col>
                                <Form.Control
                                    type="number"
                                    value={quantity}
                                    onChange={e => setQuantity(Number(e.target.value))}
                                    min="1"
                                    max="10"
                                    autoFocus
                                    required />
                                <Form.Control.Feedback type="invalid">
                                    <FormattedMessage id='project.global.validator.incorrectquantity'/>
                                </Form.Control.Feedback>
                            </Col>
                        </Form.Group>

                        <Form.Group controlId="creditCard" className="mb-3">
                            <Form.Label>
                                <FormattedMessage id="project.shopping.buyform.creditcard"/>
                            </Form.Label>
                            <Col>
                                <Form.Control
                                    type="text"
                                    value={creditCard}
                                    onChange={e => setCreditCard(e.target.value)}
                                    minLength="16"
                                    maxLength="16"
                                    required />
                                <Form.Control.Feedback type="invalid">
                                    <FormattedMessage id='project.global.validator.incorrectcreditcard'/>
                                </Form.Control.Feedback>
                            </Col>
                        </Form.Group>

                        <Form.Group>
                            <Col>
                                <Button type="submit" variant="primary">
                                    <FormattedMessage id="project.shopping.buyform.buy"/>
                                </Button>
                            </Col>
                        </Form.Group>
                    </Form>
                </Card.Body>
            </Card>
        </div>
    );
};

export default BuyForm;