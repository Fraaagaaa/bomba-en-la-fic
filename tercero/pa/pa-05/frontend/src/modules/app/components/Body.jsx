import {useSelector} from 'react-redux';
import {Route, Routes} from 'react-router';
import Container from 'react-bootstrap/Container';
import {MovieDetails, SessionDetails} from '../../catalog';

import AppGlobalComponents from './AppGlobalComponents';
import Home from './Home';
import {Login, SignUp, UpdateProfile, ChangePassword, Logout} from '../../users';
import DeliverTickets from '../../shopping/components/DeliverTickets';
import {PurchaseHistory, PurchaseCompleted} from '../../shopping';
import users from '../../users';

const Body = () => {

    const loggedIn = useSelector(users.selectors.isLoggedIn);
    const user = useSelector(users.selectors.getUser);

   return (

       <Container className="my-4 justify-content-center flex-grow-1">
            <AppGlobalComponents/>
            <Routes>
                <Route path="/*" element={<Home/>}/>
                {loggedIn && <Route path="/users/update-profile" element={<UpdateProfile/>}/>}
                {loggedIn && <Route path="/users/change-password" element={<ChangePassword/>}/>}
                {loggedIn && <Route path="/users/logout" element={<Logout/>}/>}
                {!loggedIn && <Route path="/users/login" element={<Login/>}/>}
                {!loggedIn && <Route path="/users/signup" element={<SignUp/>}/>}
                <Route path="/catalog/movie-details/:id" element={<MovieDetails/>}/>
                <Route path="/catalog/session-details/:id" element={<SessionDetails/>}/>
                {user && user.role === 'TICKETSELLER' && <Route path="/shopping/deliver-tickets" element={<DeliverTickets/>}/>}
                {user && user.role === 'USER' && <Route path="/shopping/purchase-history" element={<PurchaseHistory/>}/>}
                {user && user.role === 'USER' && <Route path="/shopping/purchase-completed" element={<PurchaseCompleted/>}/>}
            </Routes>
       </Container>

    );

};

export default Body;
