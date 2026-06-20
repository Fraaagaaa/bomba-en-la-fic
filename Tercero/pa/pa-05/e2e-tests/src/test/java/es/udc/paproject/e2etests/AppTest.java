package es.udc.paproject.e2etests;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.time.Duration;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.Select;
import org.openqa.selenium.support.ui.WebDriverWait;

public class AppTest {

    WebDriver driver;

    @BeforeEach
    public void setup() {
        driver = new ChromeDriver();
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));
        driver.manage().window().maximize();
    }

    private void login(String userName, String password) { //
        driver.get("http://localhost:5173");

        WebElement loginLink = driver.findElement(By.id("loginLink"));
        loginLink.click();

        WebElement userNameInput = driver.findElement(By.id("userName"));
        userNameInput.sendKeys(userName);

        WebElement passwordInput = driver.findElement(By.id("password"));
        passwordInput.sendKeys(password);

        WebElement loginButton = driver.findElement(By.id("loginButton"));
        loginButton.click();

        WebElement userDropdown = driver.findElement(By.id("user-dropdown"));
        assertTrue(userDropdown.getText().contains(userName));
    }


    @Test
    public void testLogin() {
        login("testviewer", "pa2526");
    }

    @Test
    public void testDeliverTickets() throws InterruptedException {
        login("testticketseller", "pa2526");

        WebElement deliverTicketsLink = driver.findElement(By.cssSelector("a[href='/shopping/deliver-tickets']"));
        deliverTicketsLink.click();

        WebElement purchaseIdInput = driver.findElement(By.id("purchaseId"));
        purchaseIdInput.clear();
        purchaseIdInput.sendKeys("3");

        WebElement creditCardInput = driver.findElement(By.id("creditCard"));
        creditCardInput.clear();
        creditCardInput.sendKeys("1234567812345678");

        WebElement submitBtn = driver.findElement(By.cssSelector("button[type='submit']"));
        submitBtn.click();

        Thread.sleep(2000);

        WebElement successAlert = driver.findElement(By.className("alert-success"));
        assertTrue(successAlert.isDisplayed(), "Debería mostrarse un mensaje de éxito en verde");

        purchaseIdInput = driver.findElement(By.id("purchaseId"));
        purchaseIdInput.clear();
        purchaseIdInput.sendKeys("3");

        creditCardInput = driver.findElement(By.id("creditCard"));
        creditCardInput.clear();
        creditCardInput.sendKeys("1234567812345678");

        submitBtn = driver.findElement(By.cssSelector("button[type='submit']"));
        submitBtn.click();

        Thread.sleep(2000);

        WebElement errorAlert = driver.findElement(By.className("alert-danger"));
        assertTrue(errorAlert.isDisplayed(), "Debería mostrarse un mensaje de error del backend");
    }

    @Test
    public void testViewSessionDetailsAsViewer() {
        login("testviewer", "pa2526");

        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(10));
        WebElement dateSelector = wait.until(ExpectedConditions.visibilityOfElementLocated(By.id("billboardDate")));
        Select select = new Select(dateSelector);
        select.selectByIndex(1);

        WebElement firstMovieLink = wait.until(ExpectedConditions.visibilityOfElementLocated(By.className("movie-link")));
        String movieTitle = firstMovieLink.getText();

        WebElement firstSessionLink = wait.until(ExpectedConditions.elementToBeClickable(By.className("session-link")));
        String sessionTime = firstSessionLink.getText();

        firstSessionLink.click();

        WebElement movieTitleElement = wait.until(ExpectedConditions.visibilityOfElementLocated(By.id("movie-title")));
        WebElement runtimeElement = driver.findElement(By.id("runtime"));
        WebElement priceElement = driver.findElement(By.id("price"));
        WebElement dateElement = driver.findElement(By.id("date"));
        WebElement timeElement = driver.findElement(By.id("time"));
        WebElement roomNameElement = driver.findElement(By.id("room-name"));
        WebElement availableSeatsElement = driver.findElement(By.id("available-seats"));

        assertTrue(runtimeElement.isDisplayed());
        assertTrue(priceElement.isDisplayed());
        assertTrue(dateElement.isDisplayed());
        assertTrue(timeElement.isDisplayed());
        assertTrue(roomNameElement.isDisplayed());
        assertTrue(availableSeatsElement.isDisplayed());

        assertEquals(movieTitle, movieTitleElement.getText());
        assertTrue(timeElement.getText().contains(sessionTime));

        WebElement quantityInput = driver.findElement(By.id("quantity"));
        WebElement creditCardInput = driver.findElement(By.id("creditCard"));
        assertTrue(quantityInput.isDisplayed());
        assertTrue(creditCardInput.isDisplayed());
    }

    @Test
    public void testBuyTickets() throws InterruptedException
    {
        // 1
        login("testviewer", "pa2526");

        // 2
        driver.get("http://localhost:5173/catalog/session-details/15");

        // 3
        WebElement pelulaComprar = driver.findElement(By.cssSelector("h4.card-title a"));
        String tituloEsperado = pelulaComprar.getText();

        // 4
        WebElement cantidad = driver.findElement(By.id("quantity"));
        cantidad.clear();
        cantidad.sendKeys("2");

        WebElement tarjeta = driver.findElement(By.id("creditCard"));
        tarjeta.clear();
        tarjeta.sendKeys("1234567812345678");

        // 5
        WebElement comprar = driver.findElement(By.cssSelector("button[type='submit']"));
        comprar.click();


        // 6: En nuestro frontend nunca devolvemos por pantalla el idenficador de la compra

        // 7
        WebElement historialCompras = driver.findElement(By.cssSelector("a[href='/shopping/purchase-history']"));
        historialCompras.click();

        // 8
        WebElement campoPelicula = driver.findElement(By.cssSelector("tbody tr:first-child td:nth-child(3)"));

        String tituloPelicula = campoPelicula.getText();

        // Validación del nombre de la película
        assertEquals(tituloEsperado, tituloPelicula, "El nombre de la película en el historial debe coincidir con el esperado");
    }

    @AfterEach
    public final void teardown() {
        if (driver != null) {
            driver.quit();
        }
    }

}
