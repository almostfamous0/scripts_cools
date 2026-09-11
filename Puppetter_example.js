const puppeteer = require('puppeteer');

(async () => {
  const browser = await puppeteer.launch({
    headless: false,
    defaultViewport: null,
    args: ['--start-maximized']
  });
  const page = await browser.newPage();

  await page.goto('https://www.google.com');

  // Type 'uol' into the search bar
  await page.type('textarea[name="q"]', 'uol');

  // Click the search button
  await page.keyboard.press('Enter');

  // Wait for the results to load
  await page.waitForNavigation();
  await page.waitForSelector('div#search');

  // Find all the links on the page
  const links = await page.evaluate(() => {
    return Array.from(document.querySelectorAll('a')).map(a => a.href);
  });

  // Find the first link that is a search result
  const firstResultHref = links.find(href => href && href.startsWith('https://www.uol.com.br'));

  // Click on the first result
  if (firstResultHref) {
    await page.goto(firstResultHref);
    console.log('Successfully navigated to the first search result.');
  } else {
    console.log('Could not find the first search result.');
  }

  // Keep the browser open for a few seconds to observe the result
  await new Promise(resolve => setTimeout(resolve, 5000));

  await browser.close();
})();
