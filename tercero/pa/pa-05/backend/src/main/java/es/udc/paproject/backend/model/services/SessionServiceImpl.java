package es.udc.paproject.backend.model.services;

import es.udc.paproject.backend.model.entities.Session;
import es.udc.paproject.backend.model.entities.SessionDao;
import es.udc.paproject.backend.model.exceptions.InstanceNotFoundException;
import es.udc.paproject.backend.model.exceptions.SessionAlreadyStartedException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDateTime;
import java.util.Optional;

@Service
@Transactional(readOnly = true)
public class SessionServiceImpl implements SessionService
{
    @Autowired
    private SessionDao sessionDao;

    @Override
    public Session viewSessionDetails(Long SessionId) throws InstanceNotFoundException, SessionAlreadyStartedException
    {
        Optional<Session> optSession = sessionDao.findById(SessionId);
        if(optSession.isEmpty())
            throw new InstanceNotFoundException("No se ha encontrado la session", SessionId);

        Session session = optSession.get();

        if(session.getSessionStartTime().withNano(0).isBefore(LocalDateTime.now().withNano(0)))
            throw new SessionAlreadyStartedException("Ya ha empezado la session", SessionId);

        return optSession.get();
    }
}
