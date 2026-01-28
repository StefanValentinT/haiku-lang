use std::collections::HashMap;
use tokio::sync::RwLock;
use tower_lsp::jsonrpc::Result;
use tower_lsp::lsp_types::*;
use tower_lsp::{Client, LanguageServer, LspService, Server};

pub struct LanguageServerBackend {
    client: Client,
    documents: RwLock<HashMap<Url, String>>,
}

#[tower_lsp::async_trait]
impl LanguageServer for LanguageServerBackend {
    async fn initialize(&self, _: InitializeParams) -> Result<InitializeResult> {
        Ok(InitializeResult {
            capabilities: ServerCapabilities {
                text_document_sync: Some(TextDocumentSyncCapability::Kind(
                    TextDocumentSyncKind::FULL,
                )),
                // No semantic highlighting
                ..Default::default()
            },
            ..Default::default()
        })
    }

    async fn initialized(&self, _: InitializedParams) {
        self.client
            .log_message(MessageType::INFO, "Hello Haiku LSP initialized")
            .await;
    }

    async fn shutdown(&self) -> Result<()> {
        Ok(())
    }

    async fn did_open(&self, params: DidOpenTextDocumentParams) {
        self.documents.write().await.insert(
            params.text_document.uri.clone(),
            params.text_document.text.clone(),
        );
        self.publish_dummy(params.text_document.uri.clone()).await;
    }

    async fn did_change(&self, params: DidChangeTextDocumentParams) {
        let text = params
            .content_changes
            .last()
            .map(|c| c.text.clone())
            .unwrap_or_default();

        self.documents
            .write()
            .await
            .insert(params.text_document.uri.clone(), text.clone());

        self.publish_dummy(params.text_document.uri.clone()).await;
    }
}

impl LanguageServerBackend {
    async fn publish_dummy(&self, uri: Url) {
        let diagnostic = Diagnostic {
            range: Range::new(Position::new(0, 0), Position::new(0, 1)),
            severity: Some(DiagnosticSeverity::INFORMATION),
            message: "Hello from the LSP.".to_string(),
            source: Some("haiku".to_string()),
            ..Default::default()
        };

        let _ = self
            .client
            .publish_diagnostics(uri, vec![diagnostic], None)
            .await;
    }
}

pub async fn run_language_server() {
    let stdin = tokio::io::stdin();
    let stdout = tokio::io::stdout();

    let (service, socket) = LspService::new(|client| LanguageServerBackend {
        client,
        documents: RwLock::new(HashMap::new()),
    });

    Server::new(stdin, stdout, socket).serve(service).await;
}
