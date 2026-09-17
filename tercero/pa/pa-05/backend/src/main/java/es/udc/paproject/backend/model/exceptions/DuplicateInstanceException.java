package es.udc.paproject.backend.model.exceptions;
// venia hecha
@SuppressWarnings("serial")
public class DuplicateInstanceException extends InstanceException {

    public DuplicateInstanceException(String name, Object key) {
    	super(name, key); 	
    }
    
}
