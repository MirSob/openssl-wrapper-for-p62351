#define TLS_ERROR_NONE          0
#define TLS_ERROR_ZERO_RETURN   1
#define TLS_ERROR_WANT_READ     2
#define TLS_ERROR_WANT_WRITE    3
#define TLS_ERROR_OTHER         4


typedef struct p62351_tls_ctx_config_s
{
	/** �Զ���Э�̵��ֽ��� */
	int renegotiate_bytes;
	/** �Զ���Э�̵�ʱ������ */
	int renegotiate_timeout;
	/** CA ��֤���ļ���·�� */
	const char *ca_file;
	/** ����֤���ļ���·�� */
	const char *cert_file;
	/** ����֤���ļ��ı������� */
	const char *cert_password;
	/** CRL �ļ�·�� */
	const char *crl_file;
	/** CRL �ļ��Զ��������� */
	int crl_update_interval;
	/** ���ֳ�ʱʱ�䣬��λΪ�� */
	int handshake_timeout;
} p62351_tls_ctx_config_t;

/**
* TLS �����Ķ���
*
* �ö�����������ȫ�����ã��Ա����ͳһ�������½� TLS ���󡣿������Ϊ����һ��
* ��������
*/
typedef struct p62351_tls_ctx_s p62351_tls_ctx_t;

/**
* TLS ���Ӷ���
*
* һ�� TLS ���Ӷ����Ӧ��һ�� TLS ���ӡ�
*/
typedef struct p62351_tls_s p62351_tls_t;

/**
* �½� TLS �����Ķ���
*
* ͬʱ�� p62351 Э������ȫ�ֳ�ʼ����
*
* @param[in] config TLS ���ò���
* @return �½������� TLS �����Ķ���NULL ��ʾʧ�ܡ�
*/
p62351_tls_ctx_t *p62351_tls_ctx_new(const p62351_tls_ctx_config_t *config);

/**
* ��ӶԶ�֤��
*
* ���������֤�ĶԶ�֤�飬����һ���ӿ�֮����ã�һ�����һ�������û�е��ù���
* ��������˵�����ܳ�����Ȩ��֤�����������֤�顣
*
* @param[in] ctx TLS �����Ķ���
* @param[in] certpath ����ӵ�֤�������ļ�·��
* @return 0 ��ʾ��ӳɹ�
*/
int p62351_tls_add_peer_cert(p62351_tls_ctx_t *ctx, const char *certpath);

/**
* �½� TLS ���Ӷ���
* ͨ�� TLS �����Ķ������µ� TLS ���Ӷ��󣬱�ʾһ�� TLS ���ӣ�ͬʱָ���ײ��
* socket ������� TLS ���ӵĽ�ɫ���ǿͻ��ˣ����� TLS ���ӵ�һ�������Ƿ���
* �ˣ����� TLS ���ӵ�һ�������Լ������ӵĶ�дģʽ������ģʽ���Ƿ�����ģʽ��
*
* Ҫ���ڵ��øú���֮ǰ��sock �Ѿ���Ӧ�ó����ʼ��������ǿͻ��ˣ�Ҫ���Ѿ��ɹ�
* ���ò���ϵͳ�ṩ��connect����������Ƿ���ˣ���Ҫ����ͨ������ϵͳ�ṩ��
* accept �����õ���������Զ˽���ͨ�ŵ� socket �����
*
* @param[in] ctx TLS �����Ķ���
* @param[in] sock �� TLS ������Ҫʹ�õ� socket �������Ӿ��
* @param[in] is_client �� TLS �����Ƿ�ͻ���
* @param[in] is_blocking �� TLS �����Ƿ�ʹ������ģʽ
* @return �½����� TLS ���Ӷ���NULL ��ʾʧ�ܡ�
*/
p62351_tls_t *p62351_tls_new(p62351_tls_ctx_t *ctx, int sock, int is_client, int is_nonblocking);

/**
* �ӶԶ˶�ȡ����
*
* @param[in] tls TLS ���Ӷ���
* @param[in] buf ��ȡ������ָ��
* @param[in] len ��ȡ��������С
* @param[out] err TLS ִ��״̬��
* @return 0 ��ʾ��ȡ�ɹ�
*/
int p62351_tls_read(p62351_tls_t *tls, char *buf, int len, int *err);

/**
* �������ݵ��Զ�
*
* @param[in] tls TLS ���Ӷ���
* @param[in] buf ��д���ݻ�����ָ��
* @param[in] len ��д���ݻ���������
* @param[out] err TLS ִ��״̬��
* @return 0 ��ʾд��ɹ�
*/
int p62351_tls_write(p62351_tls_t *tls, const char *buf, int len, int *err);

/** �ͷ� TLS ���Ӷ��� */
void p62351_tls_free(p62351_tls_t *tls);
/** �ͷ� TLS �����Ķ��� */
void p62351_tls_ctx_free(p62351_tls_ctx_t *ctx);

/**
* �õ���һ��Э���ӿڵĴ�����Ϣ�ַ�����
*
* ���ַ������ڴ���Э����ڲ�ά��������Ҫ�û��ֶ��ͷš�ÿ���̶߳���һ��������
* �洢����
*
* @return ������Ϣ�ַ���
*/
const char *p62351_get_last_error_string(void);

/** �õ�Э�̳��ļ����׼����ơ�����Ҫ�û��ֶ��ͷš� */
const char *p62351_tls_get_cipher_name(p62351_tls_t *tls);
/** �õ��Զ�֤���������������Ҫ�û��ֶ��ͷš� */
const char *p62351_tls_get_peer_cert_subject(p62351_tls_t *tls);
/** �õ��Զ�֤���ǩ���ߡ�����Ҫ�û��ֶ��ͷš� */
const char *p62351_tls_get_peer_cert_issuer(p62351_tls_t *tls);

