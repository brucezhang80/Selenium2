package org.openqa.grid.e2e.wd;

import java.net.MalformedURLException;
import java.net.URL;

import org.openqa.grid.e2e.utils.GridConfigurationMock;
import org.openqa.grid.e2e.utils.RegistryTestHelper;
import org.openqa.grid.internal.Registry;
import org.openqa.grid.selenium.SelfRegisteringRemote;
import org.openqa.grid.web.Hub;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.net.PortProber;
import org.openqa.selenium.remote.DesiredCapabilities;
import org.openqa.selenium.remote.RemoteWebDriver;
import org.testng.Assert;
import org.testng.annotations.AfterClass;
import org.testng.annotations.BeforeClass;
import org.testng.annotations.Test;

@Test(groups = { "slow", "firefox" })
public class SmokeTest {

	private Hub hub = Hub.getNewInstanceForTest(PortProber.findFreePort(), Registry.getNewInstanceForTestOnly());
	private URL hubURL = hub.getUrl();

	@BeforeClass(alwaysRun = false)
	public void prepare() throws Exception {
		hub.start();

		SelfRegisteringRemote remote = SelfRegisteringRemote.create(GridConfigurationMock.webdriverConfig(hub.getRegistrationURL()));
		remote.addFirefoxSupport();
		remote.launchRemoteServer();
		remote.registerToHub();
		RegistryTestHelper.waitForNode(hub.getRegistry(), 1);
	}

	@Test
	public void test() throws MalformedURLException, InterruptedException {
		WebDriver driver = null;
		try {
			DesiredCapabilities ff = DesiredCapabilities.firefox();
			driver = new RemoteWebDriver(new URL(hubURL + "/grid/driver"), ff);
			driver.get(hubURL + "/grid/console");
			Assert.assertEquals(driver.getTitle(), "Grid overview");
		} finally {
			if (driver != null) {
				driver.quit();
			}
		}
	}

	@AfterClass(alwaysRun = false)
	public void stop() throws Exception {
		hub.stop();
	}
}
