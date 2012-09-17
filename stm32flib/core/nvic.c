#include "stm32flib.h"

#define SCB_AIRCR										0xE000ED0C
#define SCB_AIRCR_PRIGROUP_0				8
#define SCB_AIRCR_PRIGROUP_1				9
#define SCB_AIRCR_PRIGROUP_2				10
#define SCB_AIRCR_PRIGROUP_MASK			(0x07 << SCB_AIRCR_PRIGROUP_0)

#define NVIC_ISERx(irq)							(0xE000E100 + ((irq) >> 5) * 4)
#define NVIC_ICERx(irq)							(0xE000E180 + ((irq) >> 5) * 4)
#define NVIC_ISPRx(irq)							(0xE000E200 + ((irq) >> 5) * 4)
#define NVIC_ICPRx(irq)							(0xE000E200 + ((irq) >> 5) * 4)
#define NVIC_STIR										0xE000EF00
#define NVIC_IPR										0xE000E400

static volatile uint8_t initialized = 0;
static struct list irq_registration_chain[MAX_IRQS];

void NVIC_IrqRouter(void) {
	register unsigned int irqn;
	register struct irq_registeration *registration;

	__asm__ __volatile__ (
		"mrs %0, IPSR"	"\n\t"
		"sub %0, #16"		"\n\t"
		:"=r"(irqn)
	);

	if (initialized && (irqn < MAX_IRQS)) {
		registration = (struct irq_registeration *)irq_registration_chain[irqn].head;
		while (registration != NULL) {
			registration->proc(registration->udata);
			registration = (struct irq_registeration *)registration->nod.next;
		}
	}
}

int NVIC_Init(void) {
	register uint32_t reg;
	register unsigned int i;

	if (initialized)
		return -1;

	reg = HWREG32(SCB_AIRCR);
	reg &= ~SCB_AIRCR_PRIGROUP_MASK;
	reg |= (3 << SCB_AIRCR_PRIGROUP_0);
	HWREG32_SET(SCB_AIRCR, reg);

	for (i = 0; i < MAX_IRQS; i++) {
		NVIC_SetIrqPriority(i, 15);
		irq_registration_chain[i].head = NULL;
		irq_registration_chain[i].tail = NULL;
	}

	initialized = 1;

	return 0;
}

int NVIC_SetIrqRoutine(enum_irq irq, struct irq_registeration *registration) {
#if defined(DO_PARAM_CHECKING)
	if (irq < 0 || irq >= MAX_IRQS || registration == NULL)
		return -1;
#endif

	if (!initialized)
		return -1;

	list_node_init((struct list_node *)registration);
	return list_add_tail((struct list *)&irq_registration_chain[irq],
		(struct list_node *)registration);
}

int NVIC_SetIrqPriority(enum_irq irq, unsigned int prio) {
	register uint8_t reg;

#if defined(DO_PARAM_CHECKING)
	if (irq < 0 || irq >= MAX_IRQS || prio > 15)
		return -1;
#endif

	if (!initialized)
		return -1;

	reg = HWREG8(NVIC_IPR + irq);
	reg &= ~(0x0F << 4);
	reg |= prio << 4;
	HWREG8_SET(NVIC_IPR + irq, reg);

	return 0;
}

int NVIC_GetIrqPriority(enum_irq irq) {
#if defined(DO_PARAM_CHECKING)
	if (irq < 0 || irq >= MAX_IRQS)
		return -1;
#endif

	return (HWREG8(NVIC_IPR + irq) >> 4);
}

int NVIC_EnableIrq(enum_irq irq) {
#if defined(DO_PARAM_CHECKING)
	if (irq < 0 || irq >= MAX_IRQS)
		return -1;
#endif

	if (!initialized)
		return -1;

	HWREG32_SET(NVIC_ISERx(irq), BV(irq & 0x1f));

	return 0;
}

int NVIC_DisableIrq(enum_irq irq) {
#if defined(DO_PARAM_CHECKING)
	if (irq < 0 || irq >= MAX_IRQS)
		return -1;
#endif

	if (!initialized)
		return -1;

	HWREG32_SET(NVIC_ICERx(irq), BV(irq & 0x1f));

	return 0;
}

int NVIC_IsIrqEnabled(enum_irq irq) {
#if defined(DO_PARAM_CHECKING)
	if (irq < 0 || irq >= MAX_IRQS)
			return -1;
#endif

	if (!initialized)
		return -1;

	return ((HWREG32(NVIC_ISERx(irq)) & BV(irq & 0x1f)) != 0);
}

int __inline__ NVIC_IsIrqPending(enum_irq irq) {
#if defined(DO_PARAM_CHECKING)
	if (irq < 0 || irq >= MAX_IRQS)
		return -1;
#endif

	if (!initialized)
		return -1;

	return ((HWREG32(NVIC_ISPRx(irq)) & BV(irq & 0x1f)) != 0);
}

int __inline__ NVIC_ClearIrqPending(enum_irq irq) {
#if defined(DO_PARAM_CHECKING)
	if (irq < 0 || irq >= MAX_IRQS)
		return -1;
#endif

	if (!initialized)
		return -1;

	HWREG32_SET(NVIC_ICPRx(irq), BV(irq & 0x1f));

	return 0;
}

int __inline__ NVIC_TriggerIrq(enum_irq irq) {
#if defined(DO_PARAM_CHECKING)
	if (irq < 0 || irq >= MAX_IRQS)
		return -1;
#endif

	if (!initialized)
		return -1;

	HWREG32_SET(NVIC_STIR, irq);

	return 0;
}
