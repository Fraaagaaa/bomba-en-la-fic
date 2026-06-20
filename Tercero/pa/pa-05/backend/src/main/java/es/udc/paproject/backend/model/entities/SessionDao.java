package es.udc.paproject.backend.model.entities;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.time.LocalDate;
import java.util.List;

public interface SessionDao extends JpaRepository<Session, Long> {

    @Query("SELECT s FROM Session s WHERE CAST(s.sessionStartTime AS date) = :date")
    List<Session> findByDate(@Param("date") LocalDate date);
}
