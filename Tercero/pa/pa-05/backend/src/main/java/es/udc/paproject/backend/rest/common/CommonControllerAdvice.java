package es.udc.paproject.backend.rest.common;

import java.util.List;
import java.util.Locale;
import java.util.stream.Collectors;

import es.udc.paproject.backend.model.exceptions.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.MessageSource;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.MethodArgumentNotValidException;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.ResponseStatus;

@ControllerAdvice
public class CommonControllerAdvice {
	
	private final static String INSTANCE_NOT_FOUND_EXCEPTION_CODE = "project.exceptions.InstanceNotFoundException";
	private final static String DUPLICATE_INSTANCE_EXCEPTION_CODE = "project.exceptions.DuplicateInstanceException";
	private final static String PERMISSION_EXCEPTION_CODE = "project.exceptions.PermissionException";
	private final static String SESSION_ALREADY_STARTED_EXCEPTION_CODE = "project.exceptions.SessionAlreadyStartedException";
	private final static String INCORRECT_DATE_EXCEPTION_CODE = "project.exceptions.IncorrectDateException";
	private final static String ALL_TICKETS_SOLD_EXCEPTION_CODE = "project.exceptions.AllTicketsSoldException";
	private final static String TICKETS_ALREADY_RETRIEVED_EXCEPTION_CODE = "project.exceptions.TicketsAlreadyRetrievedException";
	private final static String CREDITCARD_DOES_NOT_MATCH_EXCEPTION_CODE = "project.exceptions.CredircardDoesNotMatchException";
	
	@Autowired
	private MessageSource messageSource;
	
	@ExceptionHandler(MethodArgumentNotValidException.class)
	@ResponseStatus(HttpStatus.BAD_REQUEST)
	@ResponseBody
	public ErrorsDto handleMethodArgumentNotValidException(MethodArgumentNotValidException exception) {
				
		List<FieldErrorDto> fieldErrors = exception.getBindingResult().getFieldErrors().stream()
			.map(error -> new FieldErrorDto(error.getField(), error.getDefaultMessage())).collect(Collectors.toList());
		
		return new ErrorsDto(fieldErrors);
	}
	
	@ExceptionHandler(InstanceNotFoundException.class)
	@ResponseStatus(HttpStatus.NOT_FOUND)
	@ResponseBody
	public ErrorsDto handleInstanceNotFoundException(InstanceNotFoundException exception, Locale locale) {
		
		String nameMessage = messageSource.getMessage(exception.getName(), null, exception.getName(), locale);
		String errorMessage = messageSource.getMessage(INSTANCE_NOT_FOUND_EXCEPTION_CODE, 
				new Object[] {nameMessage, exception.getKey().toString()}, INSTANCE_NOT_FOUND_EXCEPTION_CODE, locale);

		return new ErrorsDto(errorMessage);
		
	}
	
	@ExceptionHandler(DuplicateInstanceException.class)
	@ResponseStatus(HttpStatus.BAD_REQUEST)
	@ResponseBody
	public ErrorsDto handleDuplicateInstanceException(DuplicateInstanceException exception, Locale locale) {
		
		String nameMessage = messageSource.getMessage(exception.getName(), null, exception.getName(), locale);
		String errorMessage = messageSource.getMessage(DUPLICATE_INSTANCE_EXCEPTION_CODE, 
				new Object[] {nameMessage, exception.getKey().toString()}, DUPLICATE_INSTANCE_EXCEPTION_CODE, locale);

		return new ErrorsDto(errorMessage);
		
	}
	
	@ExceptionHandler(PermissionException.class)
	@ResponseStatus(HttpStatus.FORBIDDEN)
	@ResponseBody
	public ErrorsDto handlePermissionException(PermissionException exception, Locale locale) {
		
		String errorMessage = messageSource.getMessage(PERMISSION_EXCEPTION_CODE, null, PERMISSION_EXCEPTION_CODE,
			locale);

		return new ErrorsDto(errorMessage);
		
	}

	@ExceptionHandler(SessionAlreadyStartedException.class)
	@ResponseStatus(HttpStatus.BAD_REQUEST)
	@ResponseBody
	public ErrorsDto handleSessionAlreadyStartedException(SessionAlreadyStartedException exception, Locale locale) {
		String errorMessage = messageSource.getMessage(SESSION_ALREADY_STARTED_EXCEPTION_CODE, null, SESSION_ALREADY_STARTED_EXCEPTION_CODE, locale);
		return new ErrorsDto(errorMessage);
	}

	@ExceptionHandler(IncorrectDateException.class)
	@ResponseStatus(HttpStatus.BAD_REQUEST)
	@ResponseBody
	public ErrorsDto handleIncorrectDateException(IncorrectDateException exception, Locale locale) {
		String errorMessage = messageSource.getMessage(INCORRECT_DATE_EXCEPTION_CODE, null, INCORRECT_DATE_EXCEPTION_CODE, locale);
		return new ErrorsDto(errorMessage);
	}

	// --- EXCEPCIONES AÑADIDAS PARA LAS PRUEBAS ---

	@ExceptionHandler(AllTicketsSoldException.class)
	@ResponseStatus(HttpStatus.BAD_REQUEST)
	@ResponseBody
	public ErrorsDto handleAllTicketsSoldException(AllTicketsSoldException exception, Locale locale) {
		String errorMessage = messageSource.getMessage(ALL_TICKETS_SOLD_EXCEPTION_CODE, null, ALL_TICKETS_SOLD_EXCEPTION_CODE, locale);
		return new ErrorsDto(errorMessage);
	}

	@ExceptionHandler(TicketsAlreadyRetrievedException.class)
	@ResponseStatus(HttpStatus.BAD_REQUEST)
	@ResponseBody
	public ErrorsDto handleTicketsAlreadyRetrievedException(TicketsAlreadyRetrievedException exception, Locale locale) {
		String errorMessage = messageSource.getMessage(TICKETS_ALREADY_RETRIEVED_EXCEPTION_CODE, null, TICKETS_ALREADY_RETRIEVED_EXCEPTION_CODE, locale);
		return new ErrorsDto(errorMessage);
	}

	@ExceptionHandler(CredircardDoesNotMatch.class)
	@ResponseStatus(HttpStatus.BAD_REQUEST)
	@ResponseBody
	public ErrorsDto handleCredircardDoesNotMatchException(CredircardDoesNotMatch exception, Locale locale) {
		String errorMessage = messageSource.getMessage(CREDITCARD_DOES_NOT_MATCH_EXCEPTION_CODE, null, CREDITCARD_DOES_NOT_MATCH_EXCEPTION_CODE, locale);
		return new ErrorsDto(errorMessage);
	}

}