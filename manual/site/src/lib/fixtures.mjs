/* The removed-entity fixtures stand in for tombstones the manual does not yet
   have. Keeping the gate here, rather than inside the data loader, lets a test
   exercise both directions without a build. */

export function fixturesEnabled(environment = process.env) {
	return environment.MANUAL_TEST_FIXTURES === '1';
}

export function withFixtures(committed, fixtures, environment = process.env) {
	const rows = [...(committed ?? [])];
	if (fixturesEnabled(environment)) rows.push(...(fixtures ?? []));
	return rows;
}
