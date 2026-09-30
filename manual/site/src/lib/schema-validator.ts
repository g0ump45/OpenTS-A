import Ajv2020, { type ErrorObject, type ValidateFunction } from 'ajv/dist/2020.js';

const ajv = new Ajv2020({ allErrors: true, strict: true, strictRequired: false });
const validators = new WeakMap<object, ValidateFunction>();

function validatorFor(schema: object): ValidateFunction {
	let validator = validators.get(schema);
	if (!validator) {
		validator = ajv.compile(schema);
		validators.set(schema, validator);
	}
	return validator;
}

export function contractErrors(schema: object, value: unknown): ErrorObject[] {
	const validator = validatorFor(schema);
	return validator(value) ? [] : [...(validator.errors ?? [])];
}

function errorPath(error: ErrorObject): string {
	const parts = error.instancePath
		.split('/')
		.slice(1)
		.map((part) => part.replace(/~1/g, '/').replace(/~0/g, '~'));
	if (error.keyword === 'required' && typeof error.params.missingProperty === 'string') {
		parts.push(error.params.missingProperty);
	}
	return parts.length ? parts.join('.') : '<root>';
}

export function assertContract(schema: object, value: unknown, label: string): void {
	const errors = contractErrors(schema, value);
	if (!errors.length) return;
	const details = errors.map((error) => `${errorPath(error)} ${error.message ?? 'is invalid'}`);
	throw new Error(`${label} does not satisfy its shared schema:\n  ${details.join('\n  ')}`);
}

