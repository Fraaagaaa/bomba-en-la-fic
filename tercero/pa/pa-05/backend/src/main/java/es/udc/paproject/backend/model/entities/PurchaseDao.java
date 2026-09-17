package es.udc.paproject.backend.model.entities;

import org.springframework.data.domain.Slice;
import org.springframework.data.domain.Pageable;
import org.springframework.data.repository.ListCrudRepository;

public interface PurchaseDao extends ListCrudRepository<Purchase, Long> {

    Slice<Purchase> findByUserIdOrderByPurchaseDateDesc(Long userId, Pageable pageable);
}